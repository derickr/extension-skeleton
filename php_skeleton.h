#ifndef PHP_SKELETON_H
# define PHP_SKELETON_H

extern zend_module_entry skeleton_module_entry;
# define phpext_skeleton_ptr &skeleton_module_entry

# define PHP_SKELETON_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_SKELETON)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

ZEND_BEGIN_MODULE_GLOBALS(skeleton)
ZEND_END_MODULE_GLOBALS(skeleton)

#ifdef ZTS
#define SKELETON_G(v) TSRMG(skeleton_globals_id, zend_skeleton_globals *, v)
#else
#define SKELETON_G(v) (skeleton_globals.v)
#endif

#endif	/* PHP_SKELETON_H */
