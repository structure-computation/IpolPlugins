#include <Soca/Com/SodaClient.h>
#include <QtCore/QFile>
#include <QtCore/QBuffer>
#include <QtGui/QImage>

#include "IpolACEUpdater.h"
#include <sstream>
#include <string.h>

void new_treeitem(MP& obj, QString name) {
    obj[ "_ico" ]             = "";
    obj[ "_name" ]            = name;
    obj[ "_viewable" ]        = true;
    obj[ "_children" ]        = MP::new_lst();
    obj[ "_output" ]          = MP::new_lst();
    obj[ "_context_modules" ] = MP::new_lst();
    obj[ "_context_actions" ] = MP::new_lst();
    obj[ "_name_class" ]      = "";
    obj[ "_allow_vmod" ]      = true;
}

inline void load_img( MP img, QImage& qimg)
{
    QString src = img[ "img.src" ];
    if(QFile::exists(src)) {
        qimg.load(src);
    }
    else {
        src.remove(0,22);           // Remove MIME type
        QByteArray b6;
        b6.append(src);
        QByteArray ba = QByteArray::fromBase64(b6);
        QBuffer bu(&ba);
        qimg.load(&bu,"PNG");
    }
}

inline void save_img( MP img, const QImage &qimg ) {
    // -> png
    QByteArray ba;
    QBuffer buffer( &ba );
    buffer.open( QIODevice::WriteOnly );
    qimg.save( &buffer, "PNG" );
    
    // -> base64
    QByteArray b6;
    b6.append( "data:image/png;base64," );
    b6.append( ba.toBase64() );
    
    img[ "src" ] = QString::fromAscii( b6.data(), b6.size() );
    img[ "_histo" ] = MP::new_lst();
}


bool IpolACEUpdater::run( MP mp ) {
    MP lst_img = mp[ "_children[ 0 ]._children" ];  // La liste des images
    const int nb_img = lst_img.size();              // Le nombre d'images
    for(int i = 0; i < nb_img; ++i) {
        MP img = lst_img[i];                        // La i-eme image
        QString name = img["_name"];
        
        if(img.type() == "ImgItem"){
            /// Load ImgItem into a QImage
            QString name = img[ "_name" ];
            QImage tmp_input;
            load_img(img,tmp_input);
            /// Save it into a processable file
            QString tmp_input_name = name + ".tmp.png";
            tmp_input.save(tmp_input_name,"PNG");
            
            QString tmp_output_name = "ACE_" + name + ".tmp.png";
            
            std::stringstream commandes;
            commandes << "../IpolACEPlugin/ServerPlugin/src_ace/ace";
            
            commandes << " -a " << (double) mp["alpha.val"];
            
            int num_weight = mp["weight.num"];
            switch(num_weight) {
                case 0:
                    commandes << " -w 1/r";
                    break;
                case 1:
                    commandes << " -w 1";
                    break;
                case 2:
                    commandes << " -w G:" << (double) mp["weight.lst"][num_weight]["_sigma.val"];
                    break;
                default:
                    add_message( mp, ET_Error, "Invalid weight type" );
                    return false;
            }
            
            int num_method = mp["method.num"];
            switch(num_method) {
                case 0:
                    commandes << " -m interp:" << (int) mp["method.lst"][num_method]["_level.val"];
                    break;
                case 1:
                    commandes << " -m poly:"   << ((QString) mp["method.lst"][num_method]["_degree.val"]).toStdString();
                    break;
                default:
                    add_message( mp, ET_Error, "Invalid method type" );
                    return false;
            }
            
            commandes << " " << tmp_input_name.toStdString();
            commandes << " " << tmp_output_name.toStdString();
            std::string cmd = commandes.str();
            int output = std::system(cmd.c_str());
            qDebug() << cmd.c_str();
            qDebug() << "Returned " << output;
            
            if(not output) {
                /// Retrieve image data into a ImgItem
                QImage tmp_output(tmp_output_name);
                MP new_img = MP::new_obj("ImgItem");
                new_treeitem(new_img , "ACE_" + name);
                new_img["img"] = MP::new_obj("Img");
                save_img(new_img["img"], tmp_output);
                
                /// Add result image to output set
                mp["_output[0]._children"] << new_img;
            }
            else {
                add_message( mp, ET_Error, "Error while running the application" );
            }
            
            /// clean temporary files
            QFile::remove(tmp_input_name);
            QFile::remove(tmp_output_name);
        }
        else {
            add_message( mp, ET_Error, "Unable to find image file in tree" );
        }
    }

    add_message( mp, ET_Info, "Ipol LSD -> OK" );
    qDebug() << "Ipol LSD just finish";
}

