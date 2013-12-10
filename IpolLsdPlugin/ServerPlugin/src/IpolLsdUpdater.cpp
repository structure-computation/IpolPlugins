#include <Soca/Com/SodaClient.h>
#include <QtCore/QFile>
#include <QtCore/QBuffer>
#include <QtGui/QImage>

#include <stdio.h>
#include <stdlib.h>
#include "lsd.h"
#include "IpolLsdUpdater.h"


inline void _save_img( MP outputImage, const QImage &res ) {
    // -> png
    QByteArray ba;
    QBuffer buffer( &ba );
    buffer.open( QIODevice::WriteOnly );
    res.save( &buffer, "PNG" );

    // -> base64
    QByteArray b6;
    b6.append( "data:image/png;base64," );
    b6.append( ba.toBase64() );

    outputImage[ "src" ] = QString::fromAscii( b6.data(), b6.size() );
}

/** Skip white characters and comments in a PGM file.
 */
static void skip_whites_and_comments(FILE * f)
{
    int c;
    do
    {
        while(isspace(c=getc(f))); /* skip spaces */
            if(c=='#') /* skip comments */
                while( c!='\n' && c!='\r' && c!=EOF )
                    c=getc(f);
    }
    while( c == '#' || isspace(c) );
    if( c != EOF && ungetc(c,f) == EOF )
        qDebug() << ("Error: unable to 'ungetc' while reading PGM file.");
}

/** Read a ASCII number from a PGM file.
 */
static int get_num(FILE * f)
{
    int num,c;
    
    while(isspace(c=getc(f)));
    if(!isdigit(c)) qDebug() << ("Error: corrupted PGM file.");
    num = c - '0';
    while( isdigit(c=getc(f)) ) num = 10 * num + c - '0';
    if( c != EOF && ungetc(c,f) == EOF )
        qDebug() << ("Error: unable to 'ungetc' while reading PGM file.");
    
    return num;
}

/** Read a PGM file into an double image.
 *   If the name is "-" the file is read from standard input.
 */
double * read_pgm_image_double(int * X, int * Y, char * name)
{
    FILE * f;
    int c,bin;
    int xsize,ysize,depth,x,y;
    double * image;
    
    /* open file */
    if( strcmp(name,"-") == 0 ) f = stdin;
    else f = fopen(name,"rb");
    if( f == NULL ) qDebug() << ("Error: unable to open input image file.");
    
    /* read header */
    if( getc(f) != 'P' ) qDebug() << ("Error: not a PGM file!");
    if( (c=getc(f)) == '2' ) bin = FALSE;
    else if( c == '5' ) bin = TRUE;
    else qDebug() << ("Error: not a PGM file!");
    skip_whites_and_comments(f);
    xsize = get_num(f);            /* X size */
    if(xsize<=0) qDebug() << ("Error: X size <=0, invalid PGM file\n");
    skip_whites_and_comments(f);
    ysize = get_num(f);            /* Y size */
    if(ysize<=0) qDebug() << ("Error: Y size <=0, invalid PGM file\n");
    skip_whites_and_comments(f);
    depth = get_num(f);            /* depth */
    if(depth<=0) fprintf(stderr,"Warning: depth<=0, probably invalid PGM file\n");
    /* white before data */
    if(!isspace(c=getc(f))) qDebug() << ("Error: corrupted PGM file.");
    
    /* get memory */
    image = (double *) calloc( (size_t) (xsize*ysize), sizeof(double) );
    if( image == NULL ) qDebug() << ("Error: not enough memory.");
    
    /* read data */
    for(y=0;y<ysize;y++)
        for(x=0;x<xsize;x++)
            image[ x + y * xsize ] = bin ? (double) getc(f)
            : (double) get_num(f);
        
        /* close file if needed */
        if( f != stdin && fclose(f) == EOF )
            qDebug() << ("Error: unable to close file while reading PGM file.");
        
        /* return image */
        *X = xsize;
    *Y = ysize;
    return image;
}

/** Write an int image into a PGM file.
 *   If the name is "-" the file is written to standard output.
 */
void write_pgm_image_int(int * image, int xsize, int ysize, char * name)
{
    FILE * f;
    int x,y,n,v,max,min;
    
    /* check input */
    if( image == NULL || xsize <= 0 || ysize <= 0 )
        qDebug() << ("Error: invalid input image to write_pgm_image_int.");
    
    /* check min and max values */
    max = min = 0;
    for(y=0; y<ysize; y++)
        for(x=0; x<xsize; x++)
        {
            v = image[ x + y * xsize ];
            if( v > max ) max = v;
            if( v < min ) min = v;
        }
    if( min < 0 ) fprintf(stderr,
        "Warning: write_pgm_image_int: negative values in '%s'.\n",name);
    if( max > 65535 ) fprintf(stderr,
        "Warning: write_pgm_image_int: values exceeding 65535 in '%s'.\n",name);
    
    /* open file */
    if( strcmp(name,"-") == 0 ) f = stdout;
    else f = fopen(name,"w");
    if( f == NULL ) qDebug() << ("Error: unable to open output image file.");
    
    /* write header */
    fprintf(f,"P2\n");
    fprintf(f,"%d %d\n",xsize,ysize);
    fprintf(f,"%d\n",max);
    
    /* write data */
    for(n=0,y=0; y<ysize; y++)
        for(x=0; x<xsize; x++)
        {
            fprintf(f,"%d ",image[ x + y * xsize ]);
            if(++n==8)  /* lines should not be longer than 70 characters  */
            {
                fprintf(f,"\n");
                n = 0;
            }
        }
        
        /* close file if needed */
        if( f != stdout && fclose(f) == EOF )
            qDebug() << ("Error: unable to close file while writing PGM file.");
}


bool IpolLsdUpdater::run( MP mp ) {
    MP ch = mp[ "_children[ 0 ]" ]; //on recupere l'image
    if ( ch.ok() ) {
        /// check if a image item has been provided
        QString name = ch["_name"];
        bool test_img = (ch.type() == "ImgItem");
        
        /// retrieve img file
        if(test_img){
            MP file_img = mp["_children[0]"];
            QString name = file_img[ "_name" ];
            QString file_name = file_img[ "img.src" ];
            
            /* Transform any image into a PGM */
            QImage tmp_input(file_name);
            QString file_name_2 = file_name + ".pgm";
            tmp_input.save(file_name_2,"PGM");
            
            qDebug() << "scale"      << mp["scale.val"];
            qDebug() << "sigma_coef" << mp["sigma_coef.val"];
            qDebug() << "quant"      << mp["quant.val"];
            qDebug() << "ang_th"     << mp["ang_th.val"];
            qDebug() << "log_eps"    << mp["log_eps.val"];
            qDebug() << "density_th" << mp["density_th.val"];
            qDebug() << "n_bins"     << mp["n_bins.val"];
            
            /* read input file */
            double * image;
            int X,Y;
            image = read_pgm_image_double(&X,&Y,(char*) file_name_2.toStdString().c_str());
            
            /* execute LSD */
            double * segs;
            int n;
            int * region;
            int regX,regY;
            segs = LineSegmentDetection( &n, image, X, Y,
                                         mp["scale.val"],
                                         mp["sigma_coef.val"],
                                         mp["quant.val"],
                                         mp["ang_th.val"],
                                         mp["log_eps.val"],
                                         mp["density_th.val"],
                                         mp["n_bins.val"],
                                         &region, //((QString) mp["reg"] != "") ? &region : NULL,
                                         &regX, &regY );
            /*
            for(int i = 0; i < n; i++)
            {
                for(int j = 0; j < 7; j++)
                    qDebug() << segs[i*7+j] << " ";
                qDebug() << "\n";
            }
            //*/
            /* Save results into a png image */
            write_pgm_image_int(region,regX,regY,(char*) file_name_2.toStdString().c_str());
            free( (void *) region );
            QImage tmp_output(file_name_2);
            _save_img(mp["_output[0].img"], tmp_output);
            
            /* free memory */
            free( (void *) image );
            free( (void *) segs );
            QFile::remove(file_name_2);
        }
        else {
            add_message( mp, ET_Error, "Unable to find image file in tree" );
            return false;
	}
	
	
    }

    add_message( mp, ET_Info, "Ipol LSD -> OK" );
    qDebug() << "Ipol LSD just finish";
}

