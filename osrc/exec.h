#ifndef _EXEC_H
#define _EXEC_H
static void _exec( CLOSURE clr, VALUE ref ) {
    VALUE param[10];
    uint_t params = 0;
    printf( "\nREF: %04lx", VALUE_LONG( ref ) );
    VALUE *code = value_code_ptr( ref );
    value_closure_dump( clr );
    while( code ) {
        VALUE o = *code++;
        if( o.u.v.kind != KIND_OPC )
            break;
        switch ( o.u.v.kind ) {
            case KIND_INT:
                printf( " %d", o.u.v.idx );
                break;
            case KIND_STR:
                printf( " %s", value_symbol_str( o ) );
                break;
            case KIND_OPC:
                if( o.u.v.idx ) {
                    uint_t n = o.u.v.idx;
                    VALUE name = opcodes[n].name;
                    printf( "\n-- %s", value_symbol_str( name ) );
                    if( value_eq( sym.param, name ) ) {
#include "exec_param.h"
                    }
                    else if( value_eq( sym.global, name ) ) {
#include "exec_global.h"
                    }
                    else if( value_eq( sym.cont, name ) ) {
#include "exec_cont.h"
                    }
                    else if( value_eq( sym.send, name ) ) {
#include "exec_send.h"
                    }
                    else if( value_eq( sym.new, name ) ) {
#include "exec_new.h"
                    }
                    else if( value_eq( sym.go_to, name ) ) {
#include "exec_goto.h"
                    }
                    else if( value_eq( sym.assign, name ) ) {
                        VALUE t = *code++;
                        VALUE s = *code++;
                        switch ( VALUE_KIND( s ) ) {
                            case KIND_TREF:
                                s = clr->tmp[VALUE_IDX( s )];
                                break;
                            case KIND_IREF:
                                s = value_obj_ivar( clr->tmp[0], s );
                                printf( "S:IREF %lx", VALUE_LONG( s ) );
                                break;
                        }
                        switch ( VALUE_KIND( t ) ) {
                            case KIND_TREF:
                                clr->tmp[VALUE_IDX( t )] = s;
                                break;
                            case KIND_IREF:
                                value_obj_ivar_set( clr->tmp[0], t, s );
                                printf( "IVAR %d <- %lx", VALUE_IDX( t ),
                                        VALUE_LONG( s ) );
                                break;
                            default:
                                printf( "\nILLEGAL TARGET TYPE" );
                                return;
                                break;
                        }
                    }
                    else if( value_eq( sym.primitive, name ) ) {
                        VALUE s = *code++;
                        if( prim_lib == NULL ) {
                            prim_lib =
                                    dlopen( "bin/libprimitives.so",
                                            RTLD_LAZY );
                        }
                        if( prim_lib ) {
                            CONTINUATION( *prim ) ( CLOSURE );
                            const char *name = value_symbol_str( s );
                            *( void ** )&prim = dlsym( prim_lib, name );

                            printf( "\nPRIMITIVE: %s\n", name );
                            CLOSURE c = value_closure_mk(  );
                            for( uint_t i = 0; i < params; i++ ) {
                                c->tmp[i] = param[i];
                            }
                            params = 0;
                            if( prim ) {
                                CONTINUATION cont = prim( c );
                                if( cont ) {
                                    VALUE ref = cont->ref;
                                    printf( "\nREF: %04lx",
                                            VALUE_LONG( ref ) );
                                    code = value_code_ptr( ref );
                                    clr = cont->closure;
                                }
                                else {
                                    printf( "\nNO CONTINUATION after primitive\n" );
                                    return;
                                }
                            }

                        }
                    }
                }
                break;
            case KIND_REF:
                printf( " 0x%04x", o.u.v.idx );
                break;
            case KIND_TREF:
                printf( " T%d", o.u.v.idx );
                break;
        }
    }
}
#endif
