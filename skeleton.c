#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "Zend/zend_observer.h"
#include "php_skeleton.h"

ZEND_DECLARE_MODULE_GLOBALS(skeleton)


/************************************************************************************
 * Observer
 */
static void observer_begin(zend_execute_data *execute_data)
{
}

static void observer_end(zend_execute_data *execute_data, zval *return_value)
{
}

// Runs once per zend_function on its first call
static zend_observer_fcall_handlers observer_instrument(zend_execute_data *execute_data)
{
	zend_observer_fcall_handlers handlers = {NULL, NULL};

	if (
		!execute_data->func ||
		!execute_data->func->common.function_name) {
		return handlers; // I have no handlers for this function
	}

	handlers.begin = observer_begin;
	handlers.end = observer_end;
	return handlers; // I have handlers for this function
}

/************************************************************************************
 * Execution Override
 */
static void (*skeleton_old_execute_ex)(zend_execute_data *execute_data);
static void (*skeleton_old_execute_internal)(zend_execute_data *current_execute_data, zval *return_value);

static void skeleton_execute_ex(zend_execute_data *execute_data)
{
	skeleton_old_execute_ex(execute_data);
}

static void skeleton_execute_internal(zend_execute_data *current_execute_data, zval *return_value)
{
	if (skeleton_old_execute_internal) {
		skeleton_old_execute_internal(current_execute_data, return_value);
	} else {
		execute_internal(current_execute_data, return_value);
	}
}

static void php_skeleton_init_globals(zend_skeleton_globals *skeleton_globals)
{
}

PHP_INI_BEGIN()
PHP_INI_END()

static PHP_MINIT_FUNCTION(skeleton)
{
	// zend_observer_fcall_register(observer_instrument);

	skeleton_old_execute_ex = zend_execute_ex;
	zend_execute_ex = skeleton_execute_ex;

	skeleton_old_execute_internal = zend_execute_internal;
	zend_execute_internal = skeleton_execute_internal;

	return SUCCESS;
}

static PHP_RINIT_FUNCTION(skeleton)
{
#if defined(ZTS) && defined(COMPILE_DL_SKELETON)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}

static PHP_MINFO_FUNCTION(skeleton)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "Hooks Testing Extension", "enabled");
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}

zend_module_entry skeleton_module_entry = {
	STANDARD_MODULE_HEADER,
	"skeleton",
	NULL,					/* zend_function_entry */
	PHP_MINIT(skeleton),
	NULL,					/* PHP_MSHUTDOWN */
	PHP_RINIT(skeleton),
	NULL,					/* PHP_RSHUTDOWN */
	PHP_MINFO(skeleton),
	PHP_SKELETON_VERSION,
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_SKELETON
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(skeleton)
#endif
