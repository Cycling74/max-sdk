/* 
	ext_packages.h
	API for access to Max Packages.
	Timothy Place
	Copyright 2013 - Cycling '74
*/

#ifndef _EXT_PACKAGES_H_
#define _EXT_PACKAGES_H_


/** A container for a path/filename pair,
	together with additional meta fields for special cases
	@ingroup	packages
*/
typedef struct _package_file {
	t_symbol	*filename;
	t_symbol	*name;
	short		path;
} t_package_file;


BEGIN_USING_C_LINKAGE


/** return the max path for a named package's folder

	@ingroup	packages
	@param		packagename		the name of the package
	@return						the max path id for the package's folder
 */
short packages_getpackagepath(const char *packagename);


/** return linklist of max path ids for a given subpath of a package

	@ingroup	packages
	@param		subfoldername		the name of the folder (e.g. templates, prototypes, extensions, etc)
	@param		includesysfolder	1 if you want it to include the default max copy (e.g. stuff in the C74 folder), 
									a negative number will use the specified folder as the system folder
									0 will ignore the default location
	@return							linklist of max path ids -- you are responsible for freeing this linklist.
*/
t_linklist *packages_createsubpathlist(const char *subfoldername, short includesysfolder);


/**	return a linklist of max path ids for a given subpath of a package
	and optionally a dictionary with all of the files contained therein.
	
	@ingroup	packages
	@param		subfoldername			the name of the folder (e.g. templates, prototypes, extensions, etc)
	@param		suffix_selector			a file suffix used to filter only the specified files in the path (e.g., ".maxpat")
	@param		includesysfolder		1 if you want it to include the default max copy (e.g. stuff in the C74 folder),
										a negative number will use the specified folder as the system folder
										0 will ignore the default location
	@param		subpathlist				if not NULL, a linklist is alloc'd and returned here with all of the max path ids
	@param		names_to_packagefiles	if not NULL, a dictionary is alloc'd and returned, keys are the names (suffix stripped) and the values are t_package_file instances
										the linklist in the dictionary will have its keys sorted alphabetically
	@return								the usual max error code
 */
t_max_err packages_getsubpathcontents(const char *subfoldername, const char *suffix_selector, short includesysfolder, t_linklist **subpathlist, t_dictionary **names_to_packagefiles);


END_USING_C_LINKAGE

#endif // _EXT_PACKAGES_H_
