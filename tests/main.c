#include <stdio.h>
// #include "config.h"

extern int  cfg_set_debug( int ) ;
extern int  cfg_read_config_file( char * ) ;
extern char *cfg_error_msg() ;
extern void cfg_show_configs() ;
extern void cfg_debug( const char *fmt, ...  ) ;
extern char **cfg_get_sections( int ) ;
extern char **cfg_get_keywords( int, char* ) ;
extern char *cfg_get_value( int, char *, char * ) ;
extern char **cfg_get_values( int, char *, char * ) ;
extern char **cfg_get_hash_keys( int, char *, char * ) ;
extern char *cfg_get_filename( int ) ;
extern int  cfg_get_type( int, char *, char *) ;
extern char *cfg_get_hash_value( int, char *, char *, char * ) ;
extern char *cfg_get_type_str( int, char *, char *) ;

int main( int argc, char *argv[] )
{
    char    *config_file = "conf/config.conf" ;
    char    *config_file2 = "conf/blat.conf" ;
    char    *error ;
    int     cfg_index, cfg_index2 ;

    cfg_set_debug(0) ;      // turn off debugging

    cfg_index = cfg_read_config_file( "foobar" ) ;

    if ( cfg_error_msg( cfg_index )) {
        error = cfg_error_msg( cfg_index ) ;
        fprintf( stderr,  "Error: %s", error ) ;
    }

    cfg_index = cfg_read_config_file( config_file ) ;
    if ( cfg_error_msg( cfg_index )) {
        error = cfg_error_msg( cfg_index ) ;
        fprintf( stderr,  "Error: %s", error ) ;
    }

    cfg_index2 = cfg_read_config_file( config_file2 ) ;
    if ( cfg_error_msg( cfg_index2 )) {
        error = cfg_error_msg( cfg_index2 ) ;
        fprintf( stderr,  "Error: %s", error ) ;
    }

    printf( "\n\n" ) ;
    printf( "Showing configs:\n" ) ;
    printf( "----------------------------------------------------------\n" ) ;
    cfg_show_configs() ;
    printf( "----------------------------------------------------------\n" ) ;
    printf( "\n\n" ) ;

    char **sp, **kp, **sections, **keywords, *value ;

    char *fn = cfg_get_filename( cfg_index ) ;
    printf( "%s:\n", fn ) ;
    sections = cfg_get_sections( cfg_index ) ;
    for ( sp = sections ; *sp ; sp++ ) {
        printf( "\t%s\n", *sp ) ;
        keywords = cfg_get_keywords( cfg_index, *sp ) ;
        for ( kp = keywords ; *kp ; kp++ ) {
            value = cfg_get_value( cfg_index, *sp, *kp ) ;
            printf( "\t\t\%s = \'%s\'\n", *kp, value ) ;
        }
        printf( "\n" ) ;
    }
    printf( "\n\n" ) ;

    fn = cfg_get_filename( cfg_index2 ) ;
    printf( "%s:\n", fn ) ;
    sections = cfg_get_sections( cfg_index2 ) ;
    for ( sp = sections ; *sp ; sp++ ) {
        printf( "\t%s\n", *sp ) ;
        keywords = cfg_get_keywords( cfg_index2, *sp ) ;
        for ( kp = keywords ; *kp ; kp++ ) {
            value = cfg_get_value( cfg_index2, *sp, *kp ) ;
            printf( "\t\t\%s = \'%s\'\n", *kp, value ) ;
        }
        printf( "\n" ) ;
    }

    value = cfg_get_value( -99, "poo", "bonk" ) ;
    printf( "value for index %d, section poo, keyword bonk = %s\n", -99, value ) ;


    char    **values, **vp ;
    values = cfg_get_values( 2, "domains", "ok" ) ;
    printf( "\n\nvalues for section domains and keyword ok = \n" ) ;
    if ( values == (char **)NULL ) {
        fprintf( stderr,  "No values\n" ) ;
    } else {
        for ( vp = values ; *vp ; vp++ ) {
            printf( "\t\'%s\'\n ", *vp ) ;
        }
    }

    int type ;
    char    *type_s ;

    type = cfg_get_type( 2, "domains", "ok" ) ;
    type_s = cfg_get_type_str( 2, "domains", "ok" ) ;
    printf( "Type = %s (%d) for ok\n", type_s, type ) ;

    type = cfg_get_type( 2, "domains", "worse" ) ;
    type_s = cfg_get_type_str( 2, "domains", "worse" ) ;
    printf( "Type = %s (%d) for worse\n", type_s, type ) ;

    values = cfg_get_hash_keys( 2, "hash-test", "something" ) ;
    if ( values == (char **)NULL ) {
        fprintf( stderr,  "No values\n" ) ;
    } else {
        for ( vp = values ; *vp ; vp++ ) {
            char *v ;
            v = cfg_get_hash_value( 2, "hash-test", "something", *vp ) ;
            printf( "\t%s = \'%s\'\n", *vp, v ) ;
        }
    }

    return(0) ;
}
