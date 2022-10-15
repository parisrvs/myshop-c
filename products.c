#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "/home/parijat/Codes/mylibs-c/myio/myio.h"
#include "/home/parijat/Codes/mylibs-c/myalgo/myalgo.h"

char* productfle = "products.csv";

struct product
{
    char* name;
    double price;
    char* unit;
    double stock;
    struct product* next;    
};

char* get_name(char* line)
{
    char* name = NULL;
    int len = strlen(line);
    for(int c=0; c<len; c++)
    {
        if(line[c] != ',')
        {
            name = (char*) realloc(name, sizeof(char)*(c+2));
            name[c] = line[c];
            name[c+1] = '\0';            
        }
        else
            break;
    }
    return name;
}

double get_price(char* line, int *counter)
{
    char* price = NULL;
    int count = 0, len = strlen(line);

    for(int c=(*counter)+1; c<len; c++)
    {
        if(line[c] != ',')
        {
            price = (char*) realloc(price, sizeof(char)*(count+2));
            price[count] = line[c];
            price[count+1] = '\0';
            count++;
        }
        else
            break;            
    }
    double p = atof(price);
    *counter = *counter + strlen(price);
    free(price);
    return p;
}

char* get_unit(char* line, int *counter)
{
    char* unit = NULL;
    int count = 0, len = strlen(line);
    for(int c=(*counter)+2; c<len; c++)
    {
        if(line[c] != ',')
        {
            unit = (char*) realloc(unit, sizeof(char)*(count+2));
            unit[count] = line[c];
            unit[count+1] = '\0';
            count++;
        }
        else
            break;
    }
    *counter = *counter + strlen(unit);
    return unit;
}

double get_stock(char* line, int *counter)
{
    char* stock = NULL;
    int count = 0, len = strlen(line);
    for(int c=(*counter)+3; c<len; c++)
    {
        if(line[c] != ',')
        {
            stock = (char*) realloc(stock, sizeof(char)*(count+2));
            stock[count] = line[c];
            stock[count+1] = '\0';
            count++;
        }
        else
            break;            
    }
    double p = atof(stock);
    free(stock);
    return p;
}

struct product* create_node(char* line)
{
    struct product* node = (struct product*) malloc(sizeof(struct product));
    (*node).name = get_name(line);
    int counter = strlen((*node).name);
    (*node).price = get_price(line, &counter);
    (*node).unit = get_unit(line, &counter);
    (*node).stock = get_stock(line, &counter);
    (*node).next = NULL;
    return node;
}

struct product* append_node(struct product* node, struct product* head_ptr)
{
    if(head_ptr == NULL)
        return node;
    (*node).next = head_ptr;
    return node;
}

struct product* load_products(void)
{
    FILE* fptr = fopen(productfle, "r");
    if (fptr == NULL)
        return NULL;

    struct product* node = NULL;
    struct product* head_ptr = NULL;    
    int nlines;
    char** lines = readLines(fptr, &nlines);
    for(int c=0; c<nlines; c++)
    {        
        node  = create_node(*(lines+c));
        head_ptr = append_node(node, head_ptr);
    }       

    for(int c=0; c<nlines; c++)
        free(*(lines+c));
    free(lines);
    fclose(fptr);
    return head_ptr;
}

char* clean_name(char* name)
{
    name = strip(name);
    capitalize(name);
    int len = strlen(name);
    for(int c=0; c<len; c++)
        if(name[c] == ',')
            name[c] = '-';
    return name;
}

struct product* search_product(struct product* product_pointer, char* name)
{
    struct product* ptr = product_pointer;
    while(ptr != NULL)
    {
        if( strcmp((*ptr).name, name) == 0)
            return ptr;
        else
            ptr = (*ptr).next;
    }
    return NULL;
}

struct product* get_product(struct product* product_pointer)
{
    char* name;
    struct product* node = (struct product*) malloc(sizeof(struct product));
    while(1)
    {
        printf("enter the name of the product: ");
        name = get_string();
        name = clean_name(name);
        if (search_product(product_pointer, name))
        {
            free(name);
            printf("A product with this name already exists. Enter a different name.\n");
        }
        else
        {
            (*node).name = name;
            break;
        }            
    }
    printf("enter the price of the product: ");
    (*node).price = get_double();
    printf("enter the unit of the product: ");
    (*node).unit = get_string();
    (*node).unit = clean_name((*node).unit);
    printf("enter the stock value of the product: ");
    (*node).stock = get_double();
    (*node).next = product_pointer;
    return node;
}

struct product* add_products(struct product* product_pointer)
{
    printf("Enter the number of Products you want to add: ");
    int nop = get_int();    
    for (int c=0; c<nop; c++)
        product_pointer = get_product(product_pointer);

    return product_pointer;
}

void free_products(struct product* fptr)
{
    if(fptr == NULL)
        return;
    struct product* ptr1 = fptr;
    struct product* ptr2 = fptr;
    while(ptr1 != NULL)
    {
        free((*ptr1).name);
        free((*ptr1).unit);
        ptr2 = (*ptr1).next;
        free(ptr1);
        ptr1 = ptr2;
    }
}

struct product* copy_product(struct product* ptr)
{
    int l = strlen((*ptr).name);
    struct product* newptr = (struct product*) malloc(sizeof(struct product));
    (*newptr).name = (char*) malloc(sizeof(char)*(l+1));    
    strcpy((*newptr).name, (*ptr).name);

    (*newptr).price = (*ptr).price;

    int l1 = strlen((*ptr).unit);
    (*newptr).unit = (char*) malloc(sizeof(char)*(l1+1));
    strcpy((*newptr).unit, (*ptr).unit);

    (*newptr).stock = (*ptr).stock;
    (*newptr).next = NULL;
    return newptr;
}

struct product* sorted_products(struct product* ptr, struct product* newptr)
{
    struct product* temp = NULL;
    if (newptr == NULL)
        return copy_product(ptr);
    else if ((*newptr).next == NULL)
    {
        if (strcmp((*ptr).name, (*newptr).name) > 0)
        {
            (*newptr).next = copy_product(ptr);
            return newptr;
        }
        else if (strcmp((*ptr).name, (*newptr).name) < 0)
        {
            temp = copy_product(ptr);
            (*temp).next = newptr;
            return temp;
        }
    }
    else if (strcmp((*ptr).name, (*newptr).name) < 0)
    {
        temp = copy_product(ptr);
        (*temp).next = newptr;
        return temp;
    }
    struct product* fptr = newptr;
    struct product* sptr = (*newptr).next;
    while(sptr != NULL)
    {
        if(strcmp((*ptr).name, (*sptr).name) < 0)
        {
            temp = copy_product(ptr);
            (*fptr).next = temp;
            (*temp).next = sptr;
            return newptr;
        }
        fptr = (*fptr).next;
        sptr = (*sptr).next;
    }
    (*fptr).next = copy_product(ptr);
    return newptr;
}


struct product* sort_products(struct product* head)
{   
    struct product* newptr = NULL;
    if (head == NULL)
        return NULL;
    else if ((*head).next == NULL)
    {
        newptr = copy_product(head);
        return newptr;
    }       

    struct product* ptr = head;
    struct product* nextptr = (*head).next;    

    if ((*nextptr).next == NULL && strcmp((*ptr).name, (*nextptr).name) > 0)
    {
        newptr = copy_product(nextptr);
        (*newptr).next = copy_product(ptr);
        return newptr;
    }
    else
    {
        while(ptr != NULL)
        {
            newptr = sorted_products(ptr, newptr);
            ptr = (*ptr).next;
        }
    }
    return newptr;
}

void print_products(struct product* fptr)
{
    system("clear");
    if(fptr == NULL)
    {
        printf("No product in the list.\n");
        return;
    }
    struct product* ptr1 = sort_products(fptr);
    struct product* ptr = ptr1;
    while(ptr != NULL)
    {
        printf("\nProduct Name: %-25s\t", (*ptr).name);
        printf("Price: %-15.2lf\t", (*ptr).price);
        printf("Unit: %-15s\t", (*ptr).unit);
        printf("Total Stock Value: %-15.2lf",(*ptr).stock);
        ptr = (*ptr).next;
    }
    printf("\n");
    free_products(ptr1);
}

void searchProduct(struct product* ptr)
{
    if(ptr == NULL)
    {
        printf("No product in the list.\n");
        return;
    }
    printf("Enter the name of the product you want to search: ");
    char* name = get_string();
    name = clean_name(name);
    struct product* sptr = search_product(ptr, name);
    if (sptr == NULL)
        printf("Product NOT Found\n");
    else
    {
        printf("\nProduct Name: %-25s\t", (*sptr).name);
        printf("Price: %-15.2lf\t", (*sptr).price);
        printf("Unit: %-15s\t", (*sptr).unit);
        printf("Total Stock Value: %-15.2lf\n",(*sptr).stock);
    }
    free(name);
}

void print_product(struct product* ptr)
{
    printf("\nProduct Name: %-25s\t", (*ptr).name);
    printf("Price: %-15.2lf\t", (*ptr).price);
    printf("Unit: %-15s\t", (*ptr).unit);
    printf("Total Stock Value: %-15.2lf\n",(*ptr).stock);
}

void modify_name(struct product* ptr, struct product* product_pointer)
{
    printf("Product's Name on File: %s\n", (*ptr).name);
    char* name = NULL;
    struct product* sptr = NULL;
    while(1)
    {
        printf("Enter a new Name: ");
        name = get_string();
        name = clean_name(name);
        sptr = search_product(product_pointer, name);
        if(sptr != NULL)
        {
            printf("A Product with this Name already exists. Please enter a different Name\n");
            free(name);
        }
        else
        {
            free((*ptr).name);
            (*ptr).name = name;
            break;            
        }
    }
}

void modify_price(struct product* ptr)
{
    printf("Current Price of the %s is: %.2lf\nPlease enter a new price: ", (*ptr).name, (*ptr).price);
    (*ptr).price = get_double();
}

void modify_unit(struct product* ptr)
{
    printf("Current Unit of the %s is: %s\nPlease enter a new unit: ", (*ptr).name, (*ptr).unit);
    char* unit = get_string();
    unit = clean_name(unit);
    free((*ptr).unit);
    (*ptr).unit = unit;
}

void modify_stock(struct product* ptr)
{
    printf("Current Stock Value of %s is: %.2lf\nPlease enter a new stock value: ", (*ptr).name, (*ptr).stock);
    (*ptr).stock = get_double();
}

void modify_product(struct product* product_pointer)
{    
    if(product_pointer == NULL)
    {
        printf("No products in the list.\n");
        return;
    }
    int c;
    printf("Enter the name of the product: ");
    char* name = get_string();
    name = clean_name(name);
    struct product* sptr = search_product(product_pointer, name);
    if (sptr == NULL)
    {
        free(name);
        printf("This product does not exist\n");
        return;
    }
    while(1)
    {
        print_product(sptr);
        printf("Enter 1 to modify Name, 2 to modify Price, 3 to modify Unit, 4 to modify Stock Value and 5 to Return: ");
        c = get_int();
        if (c == 1)
            modify_name(sptr, product_pointer);
        else if (c == 2)
            modify_price(sptr);
        else if (c == 3)
            modify_unit(sptr);
        else if (c == 4)
            modify_stock(sptr);
        else if (c == 5)
            break;
        else
            printf("Invalid Input. Try Again.\n");
    }
    free(name);
}

struct product* deleteProduct(struct product* ptr, char* name)
{
    struct product* ptr1 = NULL, *ptr2 = NULL;
    if (strcmp((*ptr).name, name) == 0)
    {
        ptr1 = (*ptr).next;
        free((*ptr).name);
        free((*ptr).unit);
        free(ptr);
        return ptr1;
    }
    else
    {
        ptr1 = ptr;
        ptr2 = (*ptr).next;
    }
    while(ptr2 != NULL)
    {
        if (strcmp((*ptr2).name, name) == 0)
        {
            (*ptr1).next = (*ptr2).next;
            free((*ptr2).name);
            free((*ptr2).unit);
            free(ptr2);            
            break;
        }        
        else
        {
            ptr1 = (*ptr1).next;
            ptr2 = (*ptr2).next;
        }
    }    
    return ptr;
}

struct product* delete_product(struct product* ptr)
{
    if (ptr == NULL)
    {
        printf("No products in the list.\n");
        return NULL;
    }
    printf("Enter the Name of the Product you want to Delete: ");
    char* name = get_string();
    name = clean_name(name);
    struct product* sptr = search_product(ptr, name);
    if (sptr == NULL)
    {
        free(name);
        printf("This product does not exist\n");
        return ptr;
    }
    while(1)
    {
        printf("Are you sure you want to remove %s from the list\nEnter y to continue and n to return: ", (*sptr).name);
        char c = get_char();
        if (c == 'y')
            break;
        else if (c == 'n')
        {
            free(name);
            return ptr;
        }
        else
            printf("Invalid Input. Try gain.\n");
    }
    sptr = deleteProduct(ptr, name);
    free(name);
    return sptr;
}

int write_products(struct product* ptr)
{
    if (ptr == NULL)
        return remove(productfle);

    FILE* fptr = fopen(productfle, "w");
    if (fptr == NULL)
        return 1;   

    struct product* ptr1 = sort_products(ptr);
    struct product* ptr2 = ptr1;
        
    while(ptr2 != NULL)
    {
        fprintf(fptr, "%s,",(*ptr2).name);
        fprintf(fptr, "%.2lf,", (*ptr2).price);
        fprintf(fptr, "%s,", (*ptr2).unit);
        fprintf(fptr, "%.2lf\n", (*ptr2).stock);
        ptr2 = (*ptr2).next;
    }
    fclose(fptr);
    free_products(ptr1);
    return 0;
}

void myproducts(void)
{
    struct product* product_pointer = load_products();
    if (product_pointer == NULL)
        printf("There are no products.\n\n");
    
    int c;
    while(1)
    {
        printf("Enter 1 to exit and update file, 2 to add products, 3 to search products, 4 to delete products, 5 to modify products, 6 to view products: ");
        c = get_int();
        if (c == 1)
            break;
        else if (c == 2)
            product_pointer = add_products(product_pointer);
        else if (c==6)
            print_products(product_pointer);
        else if (c == 3)
            searchProduct(product_pointer);
        else if (c == 5)
            modify_product(product_pointer);
        else if (c == 4)
            product_pointer = delete_product(product_pointer);
        else
            printf("Invalid Input. Try again\n");
    }
    write_products(product_pointer);
    free_products(product_pointer);
}