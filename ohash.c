/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2014 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_ohash.h"

/* {{{ proto string ohash(object any)
   Return address of object */
PHP_FUNCTION(ohash)
{
	zval *thing;
	void *zaddress;
	char *hash;
	size_t hlen;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &thing) != SUCCESS) {
	    return;
	}
	
	if (!thing) {
	    /* throw some exception */
	    return;
	}
	
	switch (Z_TYPE_P(thing)) {
	    case IS_OBJECT:
	        zaddress = zend_object_store_get_object(thing TSRMLS_CC);
	    break;
	    
	    default:
	        zaddress = &thing->value;
	}
	
	hlen = spprintf(
	    &hash, 0, "%p", zaddress);
	
	RETURN_STRINGL(hash, hlen, 0);
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(ohash)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "ohash support", "enabled");
	php_info_print_table_end();
}
/* }}} */

ZEND_BEGIN_ARG_INFO_EX(php_ohash_arginfo, 0, 0, 1)
    ZEND_ARG_INFO(0, object)
ZEND_END_ARG_INFO()

/* {{{ ohash_functions[]
 */
const zend_function_entry ohash_functions[] = {
	PHP_FE(ohash,  php_ohash_arginfo)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in ohash_functions[] */
};
/* }}} */

/* {{{ ohash_module_entry
 */
zend_module_entry ohash_module_entry = {
	STANDARD_MODULE_HEADER,
	"ohash",
	ohash_functions,
	NULL,
	NULL,
	NULL,
	NULL,
	PHP_MINFO(ohash),
	PHP_OHASH_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_OHASH
ZEND_GET_MODULE(ohash)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
