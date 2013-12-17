#include <Soca/Com/SodaClient.h>
#include <QtCore/QFile>
#include <QtCore/QBuffer>
#include <QtGui/QImage>

#include "IpolSCAUpdater.h"
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


bool IpolSCAUpdater::run( MP mp ) {
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
            QString extension;
            if(name.endsWith(".png"))
                extension = "";
            else
                extension = ".png";
            QString tmp_input_name = name + extension;
            tmp_input.save(tmp_input_name,"PNG");
            
            
            QString tmp_output_name_0 = "SCA_sim_gray_" + name + extension;
            QString tmp_output_name_1 = "SCA_loc_gray_" + name + extension;
            QString tmp_output_name_2 = "SCA_glo_gray_" + name + extension;
            QString tmp_output_name_3 = "SCA_sim_rgb_" + name + extension;
            QString tmp_output_name_4 = "SCA_loc_rgb_" + name + extension;
            QString tmp_output_name_5 = "SCA_glo_rgb_" + name + extension;
            
            std::stringstream commandes;
            commandes << "../IpolSCAPlugin/ServerPlugin/src_sca/poisson_lca";
            commandes << " -t " << (double) mp["thresold.val"];
            commandes << " -a " << (double) mp["gradient_amplification.val"];
            commandes << " -b " << (double) mp["gradient_power.val"];
            commandes << " " << tmp_input_name.toStdString();
            commandes << " " << tmp_output_name_0.toStdString();
            commandes << " " << tmp_output_name_1.toStdString();
            commandes << " " << tmp_output_name_2.toStdString();
            commandes << " " << tmp_output_name_3.toStdString();
            commandes << " " << tmp_output_name_4.toStdString();
            commandes << " " << tmp_output_name_5.toStdString();
            std::string cmd = commandes.str();
            int output = std::system(cmd.c_str());
            qDebug() << cmd.c_str();
            qDebug() << "Returned " << output;
            
            if(not output) {
                QString output_name;
                int output_num = mp["algorithm.num"];
                switch(output_num) {
                    case 0:
                        output_name = tmp_output_name_0;
                        break;
                    case 1:
                        output_name = tmp_output_name_1;
                        break;
                    case 2:
                        output_name = tmp_output_name_2;
                        break;
                    case 3:
                        output_name = tmp_output_name_3;
                        break;
                    case 4:
                        output_name = tmp_output_name_4;
                        break;
                    case 5:
                        output_name = tmp_output_name_5;
                        break;
                }
                /// Retrieve image data into a ImgItem and then into the output
                QImage output(output_name);
                MP new_img = MP::new_obj("ImgItem");
                new_treeitem(new_img , output_name);
                new_img["img"] = MP::new_obj("Img");
                save_img(new_img["img"], output);
                mp["_output[0]._children"] << new_img;
            }
            else {
                add_message( mp, ET_Error, "Error while running the application" );
            }
            
            /// clean temporary files
            QFile::remove(tmp_input_name);
            QFile::remove(tmp_output_name_0);
            QFile::remove(tmp_output_name_1);
            QFile::remove(tmp_output_name_2);
            QFile::remove(tmp_output_name_3);
            QFile::remove(tmp_output_name_4);
            QFile::remove(tmp_output_name_5);
            QFile::remove("results.txt");
        }
        else {
            add_message( mp, ET_Error, "Unable to find image file in tree" );
        }
    }

    add_message( mp, ET_Info, "Ipol SCA -> OK" );
    qDebug() << "Ipol SCA just finish";
}

