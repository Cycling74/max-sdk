#ifndef _EXT_XMLTREE_H_
#define _EXT_XMLTREE_H_

#ifdef __cplusplus
extern "C" {
#endif

// opaque type definitions

typedef struct _xmltree_node t_xmltree_node;
typedef struct _xmltree_charnode t_xmltree_charnode ;
typedef struct _xmltree_text t_xmltree_text;
typedef struct _xmltree_comment t_xmltree_comment;
typedef struct _xmltree_cdata t_xmltree_cdata;
typedef struct _xmltree_attribute t_xmltree_attribute;
typedef struct _xmltree_element t_xmltree_element;
typedef struct _xmltree_document t_xmltree_document;

// prototypes

// xmltree_node
t_max_err xmltree_node_addinterface(t_class *c);
t_max_err xmltree_node_sortchildlist(t_xmltree_node *x, long cmpfn(void *, void *));
t_max_err xmltree_node_insertbefore(t_xmltree_node *x, t_xmltree_node *newchild, t_xmltree_node *refchild);
t_max_err xmltree_node_replacechild(t_xmltree_node *x, t_xmltree_node *newchild, t_xmltree_node *refchild);
t_max_err xmltree_node_removechild(t_xmltree_node *x, t_xmltree_node *refchild);
t_max_err xmltree_node_appendchild(t_xmltree_node *x, t_xmltree_node *newchild);
t_atom_long xmltree_node_haschildnodes(t_xmltree_node *x);
t_xmltree_node *xmltree_node_clonenode(t_xmltree_node *x, long deep);
t_max_err xmltree_node_removeallchildren(t_xmltree_node *x);
t_max_err xmltree_node_nodevalue(t_xmltree_node *x, void *attr, long ac, t_atom *av);
t_max_err xmltree_node_getnodevalue(t_xmltree_node *x, void *attr, long *ac, t_atom **av);
t_max_err xmltree_node_setnodevalasstring(t_xmltree_node *x, char *s);
t_max_err xmltree_node_getnodevalasstring(t_xmltree_node *x, long *len, char **s);
t_max_err xmltree_node_new(t_xmltree_node *x, t_symbol *nodetype);
t_max_err xmltree_node_free(t_xmltree_node *x);
// utils
t_symbol *xmltree_node_getnodevalue_sym(t_xmltree_node *x);
t_max_err xmltree_node_nodevalue_sym(t_xmltree_node *x, t_symbol *s);
t_atom_long xmltree_node_getnodevalue_long(t_xmltree_node *x);
t_max_err xmltree_node_nodevalue_long(t_xmltree_node *x, long c);
float xmltree_node_getnodevalue_float(t_xmltree_node *x);
t_max_err xmltree_node_nodevalue_float(t_xmltree_node *x, float f);
long xmltree_node_getnodevalue_sym_array(t_xmltree_node *x, long max, t_symbol **vals);
t_max_err xmltree_node_nodevalue_sym_array(void *x, long count, t_symbol **vals);
long xmltree_node_getnodevalue_long_array(t_xmltree_node *x, long max, t_atom_long *vals);
t_max_err xmltree_node_nodevalue_long_array(void *x, long count, long *vals);
long xmltree_node_getnodevalue_float_array(t_xmltree_node *x, long max, float *vals);
t_max_err xmltree_node_nodevalue_float_array(void *x, long count, float *vals);


// xmltree_charnode
t_max_err xmltree_charnode_addinterface(t_class *c);
char *xmltree_charnode_substringdata(t_xmltree_charnode *x, long offset, long count);
t_max_err xmltree_charnode_appenddata(t_xmltree_charnode *x, char *data);
t_max_err xmltree_charnode_insertdata(t_xmltree_charnode *x, long offset, char *data);
t_max_err xmltree_charnode_deletedata(t_xmltree_charnode *x, long offset, long count);
t_max_err xmltree_charnode_replacedata(t_xmltree_charnode *x, long offset, long count, char *data);
t_max_err xmltree_charnode_new(t_xmltree_charnode *x, t_symbol *nodetype);
t_max_err xmltree_charnode_free(t_xmltree_charnode *x);

// xmltree_document
void xmltree_document_filename(t_xmltree_document *x, t_object *attr, long argc, t_atom *argv);
t_max_err xmltree_document_read(t_xmltree_document *x, t_symbol *s, long ac, t_atom *av);
t_max_err xmltree_document_write(t_xmltree_document *x, t_symbol *s, long ac, t_atom *av);
void xmltree_node_write(t_xmltree_node *x, t_filehandle fh, long depth);
void xmltree_document_print(t_xmltree_document *x);
t_xmltree_element *xmltree_document_createelement(t_xmltree_document *x, t_symbol *tagname);
t_xmltree_text *xmltree_document_createtextnode(t_xmltree_document *x, char *data);
t_xmltree_comment *xmltree_document_createcomment(t_xmltree_document *x, char *data);
t_xmltree_cdata *xmltree_document_createcdatasection(t_xmltree_document *x, char *data);
t_xmltree_attribute *xmltree_document_createattribute(t_xmltree_document *x, t_symbol *name);
t_linklist *xmltree_document_getelementsbytagname(t_xmltree_document *x, t_symbol *tagname);
void xmltree_document_xmlparse_element_start(t_xmltree_document *x, const char *el, const char **attr);
void xmltree_document_xmlparse_element_end(t_xmltree_document *x, const char *el);
void xmltree_document_xmlparse_default(t_xmltree_document *x, const char *s, int len);
void xmltree_document_xmlparse_characterdata(t_xmltree_document *x, const char *s, int len);
void xmltree_document_xmlparse_cdata_start(t_xmltree_document *x);
void xmltree_document_xmlparse_cdata_end(t_xmltree_document *x);
void xmltree_document_xmlparse_comment(t_xmltree_document *x, const char *s);
void xmltree_document_xmlparse_doctype_start(t_xmltree_document *x, const char *s);
void xmltree_document_xmlparse_doctype_end(t_xmltree_document *x);
void xmltree_document_createheader(t_xmltree_document *x, t_symbol *encoding);
void xmltree_document_createprocessinginstruction(t_xmltree_document *x, t_symbol *target, t_symbol *data);
void *xmltree_document_new(t_symbol *s, long argc, t_atom *argv);
void xmltree_document_free(t_xmltree_document *x);

// xmltree_element
t_max_err xmltree_element_getattribute(t_xmltree_element *x, t_symbol *attrname, long *ac, t_atom **av);
t_max_err xmltree_element_setattribute(t_xmltree_element *x, t_symbol *attrname, long ac, t_atom *av);
t_max_err xmltree_element_removeattribute(t_xmltree_element *x, t_symbol *attrname);
t_xmltree_attribute *xmltree_element_getattributenode(t_xmltree_element *x, t_symbol *attrname);
t_xmltree_attribute *xmltree_element_setattributenode(t_xmltree_element *x, t_xmltree_attribute *attr);
t_xmltree_attribute * xmltree_element_removeattributenode(t_xmltree_element *x, t_xmltree_attribute *attr);
t_linklist *xmltree_element_getelementsbytagname(t_xmltree_element *x, t_symbol *tagname);
long xmltree_element_symcompare(t_xmltree_attribute *x,t_symbol *name);
void *xmltree_element_new(t_symbol *s, long argc, t_atom *argv);
void xmltree_element_free(t_xmltree_element *x);
// utils
t_symbol *xmltree_element_getattribute_sym(t_xmltree_element *x, t_symbol *attrname);
t_max_err xmltree_element_setattribute_sym(t_xmltree_element *x, t_symbol *attrname, t_symbol *s);
t_atom_long xmltree_element_getattribute_long(t_xmltree_element *x, t_symbol *attrname);
t_max_err xmltree_element_setattribute_long(t_xmltree_element *x, t_symbol *attrname, t_atom_long c);
float xmltree_element_getattribute_float(t_xmltree_element *x, t_symbol *attrname);
t_max_err xmltree_element_setattribute_float(t_xmltree_element *x, t_symbol *attrname, float f);
long xmltree_element_getattribute_sym_array(t_xmltree_element *x, t_symbol *attrname, long max, t_symbol **vals);
t_max_err xmltree_element_setattribute_sym_array(void *x, t_symbol *attrname, long count, t_symbol **vals);
long xmltree_element_getattribute_long_array(t_xmltree_element *x, t_symbol *attrname, long max, t_atom_long *vals);
t_max_err xmltree_element_setattribute_long_array(void *x, t_symbol *attrname, long count, long *vals);
long xmltree_element_getattribute_float_array(t_xmltree_element *x, t_symbol *attrname, long max, float *vals);
t_max_err xmltree_element_setattribute_float_array(void *x, t_symbol *attrname, long count, float *vals);

// xmltree_attribute
long xmltree_attr_symcompare(t_xmltree_attribute *x,t_symbol *name);
void *xmltree_attribute_new(t_symbol *s, long argc, t_atom *argv);
void xmltree_attribute_free(t_xmltree_attribute *x);

// xmltree_text
void *xmltree_text_new(t_symbol *s, long argc, t_atom *argv);
t_xmltree_text *xmltree_text_splittext(t_xmltree_text *x, long offset);
void xmltree_text_free(t_xmltree_text *x);

// xmltree_comment
void *xmltree_comment_new(t_symbol *s, long argc, t_atom *argv);
void xmltree_comment_free(t_xmltree_comment *x);

// xmltree_cdata
void *xmltree_cdata_new(t_symbol *s, long argc, t_atom *argv);
t_xmltree_cdata *xmltree_cdata_splittext(t_xmltree_cdata *x, long offset);
void xmltree_cdata_free(t_xmltree_cdata *x);

#ifdef __cplusplus
}
#endif
	
#endif //_EXT_XMLTREE_H_
