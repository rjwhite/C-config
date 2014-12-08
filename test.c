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
extern int     cfg_get_type( int, char *, char * ) ;

int main( int argc, char *argv[] )
{
    char    *config_file, *error, *value ;
    char    **hkp, **hash_keys, **values, **keywords, **sections ;
    char    **sp, **kp, **vp, *hash_key, *type_s ;
    char    *keyword, *section ;
    int     cfg_index, type ;

    cfg_index = cfg_read_config_file( "test.conf" ) ;

    if ( cfg_error_msg( cfg_index )) {
        error = cfg_error_msg( cfg_index ) ;
        fprintf( stderr,  "Error: %s", error ) ;
    }

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
}
