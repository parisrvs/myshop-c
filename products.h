struct product* create_node(char*);

struct product* append_node(struct product* node, struct product* head_ptr);

char* get_name(char* line);

double get_price(char* line, int *counter);

char* get_unit(char* line, int *counter);

double get_stock(char* line, int *counter);

struct product* load_products(void);

char* clean_name(char* name);

struct product* search_product(struct product* product_pointer, char* name);

struct product* get_product(struct product* product_pointer);

struct product* add_products(struct product* product_pointer);

void free_products(struct product* fptr);

struct product* copy_product(struct product* ptr);

struct product* sorted_products(struct product* ptr, struct product* newptr);

struct product* sort_products(struct product* head);

void print_products(struct product* fptr);

void searchProduct(struct product* ptr);

void print_product(struct product* ptr);

void modify_name(struct product* ptr, struct product* product_pointer);

void modify_price(struct product* ptr);

void modify_unit(struct product* ptr);

void modify_stock(struct product* ptr);

void modify_product(struct product* product_pointer);

struct product* deleteProduct(struct product* ptr, char* name);

struct product* delete_product(struct product* ptr);

void myproducts(void);