#if defined(HAVE_SSL) && !defined(IN_MODULE)

#ifndef __ssl_h__
#define __ssl_h__

#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/rand.h>

/* OpenSSL version compatibility layer */
#if OPENSSL_VERSION_NUMBER >= 0x10100000L
#define BX_SSL_CLIENT_METHOD() TLS_client_method()
#define BX_SSL_SERVER_METHOD() TLS_server_method()
#define BX_SSL_SET_MIN_PROTO(ctx, ver) SSL_CTX_set_min_proto_version(ctx, ver)
#else
#define BX_SSL_CLIENT_METHOD() SSLv23_client_method()
#define BX_SSL_SERVER_METHOD() SSLv23_server_method()
#define BX_SSL_SET_MIN_PROTO(ctx, ver) SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3 | SSL_OP_NO_TLSv1 | SSL_OP_NO_TLSv1_1)
#endif

#ifndef TRUE
#define TRUE 0
#endif
#ifndef FALSE
#define FALSE 1
#endif

#define CHK_NULL(x) if ((x)==NULL) { say("SSL error - NULL data form server"); close_server(refnum, empty_string); return(-1); }
#define CHK_ERR(err,s) if ((err)==-1) {  say("SSL prime error - %s",s); close_server(refnum, empty_string); return(-1); }
#define CHK_SSL(err) if ((err)==-1) {  say("SSL CHK error - %d %d",err,SSL_get_error(server_list[refnum].ssl_fd, err)); close_server(refnum, empty_string); return(-2); }

void SSL_show_errors(void);

/* Make these what you want for cert & key files */

/*extern    SSL_CTX* ctx;*/
/*extern    SSL_METHOD *meth;*/

#endif
#endif
