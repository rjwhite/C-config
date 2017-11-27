#include <stdio.h>
#include "config.h"

extern int     cfg_read_config_file( char * ) ;
extern char    **cfg_get_sections( int ) ;
extern char    **cfg_get_hash_keys( int, char *, char *) ;
extern char    *cfg_get_hash_value( int, char *, char *, char *) ;
extern char    **cfg_get_keywords( int, char * ) ;
extern char    *cfg_get_value( int, char *, char * ) ;
extern char    **cfg_get_values( int, char *, char * ) ;
extern char    *cfg_error_msg( int ) ;
extern char    *cfg_get_type_str( int, char *, char * ) ;
extern char    *cfg_get_filename( int ) ;
extern char    *cfg_get_version() ;
extern int     cfg_get_type( int, char *, char * ) ;

int main( int argc, char *argv[] )
{
    char    *config_file, *error, *value ;
    char    **hkp, **hash_keys, **values, **keywords, **sections ;
    char    **sp, **kp, **vp, *hash_key, *type_s ;
    char    *keyword, *section, *filename ;
    int     cfg_index, type, i ;
    char    *configs[] = { "conf/test.conf", "conf/test2.conf" } ;

    printf( "version of library is %s\n", cfg_get_version() ) ;

    cfg_set_debug(0) ;      /* turn debugging off (default) */
    cfg_debug( "This won't print since debugging is off\n" ) ;

    for ( i=0 ; i < sizeof( configs ) / sizeof( configs[0]) ; i++ ) {
        cfg_index = cfg_read_config_file( configs[i] ) ;
        if ( cfg_error_msg( cfg_index )) {
            error = cfg_error_msg( cfg_index ) ;
            fprintf( stderr,  "Error: %s", error ) ;
            continue ;
        }

        /* get the filename for the config (we already know this) */
        filename = cfg_get_filename( cfg_index ) ;
        printf( "config filename for config index number %d is %s\n\n",
            cfg_index, filename ) ;

        sections = cfg_get_sections( cfg_index ) ;
        for ( sp = sections ; *sp ; sp++ ) {
            section = *sp ;
            printf( "%s\n", section ) ;
            keywords = cfg_get_keywords( cfg_index, *sp ) ;
            for ( kp = keywords ; *kp ; kp++ ) {
                keyword = *kp ;
                type = cfg_get_type( cfg_index, section, keyword ) ;
                type_s = cfg_get_type_str( cfg_index, section, keyword ) ;
                printf( "\t%s (%s)\n", keyword, type_s ) ;

                switch ( type ) {
                case TYPE_SCALAR:
                    value = cfg_get_value( cfg_index, section, keyword ) ;
                    printf( "\t\t\'%s\'\n", value ) ;
                    break ;
                case TYPE_ARRAY:
                    values = cfg_get_values( cfg_index, section, keyword ) ;
                    for ( vp = values ; *vp ; vp++ ) {
                        printf( "\t\t\'%s\'\n", *vp ) ;
                    }
                    break ;
                case TYPE_HASH:
                    hash_keys = cfg_get_hash_keys( cfg_index, section, keyword ) ;
                    for ( hkp = hash_keys ; *hkp ; hkp++ ) {
                        hash_key = *hkp ;
                        value = cfg_get_hash_value( cfg_index, section, keyword, hash_key ) ;
                        printf( "\t\t%s = \'%s\'\n", hash_key, value ) ;
                    }
                    break ;
                }
            }
        }
        printf( "\n\n" ) ;
    }
    return(0) ;
}
