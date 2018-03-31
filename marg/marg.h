
typedef short int id;

typedef struct option_struct {id id;
	       		      char short_option;
	       		      char *long_option;
			      short int has_operand;
			      short int called;
			      char *operand;
}option_struct;

typedef option_struct *p_opt_struct;

typedef p_opt_struct *margstructs; 


p_opt_struct *margcreate(char *prog_name, int argc, char *argv[], size_t n_opt, char shopt[], char *longopt[], short int has_operand[]);
int margfree(p_opt_struct *all_options, size_t n_all_opt);

































