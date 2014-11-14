#include <string.h>
#include "CUnit/Basic.h"
#include <stdlib.h>
#include "db_test.h"


int compare(void *left, void *right) {
  return(strcmp((const char *) left, (const char *) right));
}

comparator cmp = &compare;

int init_suite_1(void)
{
  return 0;
}

int clean_suite_1(void)
{
  return 0;
}


int init_suite_2(void)
{
  return 0;
}

int clean_suite_2(void)
{
  return 0;
}


void testCREATE_DB(void){
  struct node *first_node = create_db("First", "1");
  struct node *second_node = create_db("Second", "2");
  CU_ASSERT(strcmp(first_node->key, "First") == 0);
  CU_ASSERT(strcmp(first_node->value, "1") == 0);
  CU_ASSERT(first_node->right == NULL);
  CU_ASSERT(first_node->left == NULL);
  CU_ASSERT(strcmp(second_node->key, "Second") == 0);
  CU_ASSERT(strcmp(second_node->value, "2") == 0);
  CU_ASSERT(second_node->right == NULL);
  CU_ASSERT(second_node->left == NULL);
  destroy(&first_node);
  destroy(&second_node);
}


void testEXTRACT_VALUE(void){
  struct node *first_node = create_db("First", "1");
  struct node *second_node = create_db("Second", "");
  struct node *third_node = create_db("Third", "Hej Hopp");
  CU_ASSERT(strcmp(extract_value(first_node), first_node->value) == 0);
  CU_ASSERT(strcmp(extract_value(second_node), second_node->value) == 0);
  CU_ASSERT(strcmp(extract_value(third_node), third_node->value) == 0);
  destroy(&first_node);
  destroy(&second_node);
  destroy(&third_node);
}

void testUPDATE_VALUE(void){
  struct node *first_node = create_db("First", "1");
  struct node *second_node = create_db("Second", "");
  struct node *third_node = create_db("Third", "Hej Hopp");
  update_value((&first_node), "Oj oj");
  update_value((&second_node), "Haha");
  update_value((&third_node), "");
  CU_ASSERT(strcmp(first_node->value, "Oj oj") == 0);
  CU_ASSERT(strcmp(second_node->value, "Haha") == 0);
  CU_ASSERT(strcmp(third_node->value, "") == 0);
  destroy(&first_node);
  destroy(&second_node);
  destroy(&third_node);
}

void testADD_ITEM(void){
  struct node *db = create_db("Adam", "1");
  add_item("Berta", "2", &db, cmp);
  add_item("Curt", "3", &db, cmp);
  /*This should be balanced 
       A          B
        \   ->   / \
         B      A   C
          \
           C
  */
  CU_ASSERT(strcmp(db->key, "Berta") == 0);  
  CU_ASSERT(strcmp(db->right->key, "Curt") == 0);
  CU_ASSERT(db->right->left == NULL);
  CU_ASSERT(db->right->right == NULL);
  CU_ASSERT(strcmp(db->left->key, "Adam") == 0);
  CU_ASSERT(db->left->left == NULL);
  CU_ASSERT(db->left->right == NULL);
  destroy_db(db);
  
  struct node *db2 = create_db("Curt", "3");
  add_item("Berta", "2", &db2, cmp);
  add_item("Adam", "1", &db2, cmp);
  /*This should be balanced 
      C          B
     /    ->    / \
    B          A   C
   /       
  A         
  */
  CU_ASSERT(strcmp(db2->key, "Berta") == 0);  
  CU_ASSERT(strcmp(db2->right->key, "Curt") == 0);
  CU_ASSERT(db2->right->left == NULL);
  CU_ASSERT(db2->right->right == NULL);
  CU_ASSERT(strcmp(db2->left->key, "Adam") == 0);
  CU_ASSERT(db2->left->left == NULL);
  CU_ASSERT(db2->left->right == NULL);
  destroy_db(db2);

  struct node *db3 = create_db("Curt", "3");
  add_item("Adam", "1", &db3, cmp);
  add_item("Berta", "2", &db3, cmp);
  /*This should be balanced 
      C          B
     /    ->    / \
    A          A   C
     \     
      B
  */
  CU_ASSERT(strcmp(db3->key, "Berta") == 0);  
  CU_ASSERT(strcmp(db3->right->key, "Curt") == 0);
  CU_ASSERT(db3->right->left == NULL);
  CU_ASSERT(db3->right->right == NULL);
  CU_ASSERT(strcmp(db3->left->key, "Adam") == 0);
  CU_ASSERT(db3->left->left == NULL);
  CU_ASSERT(db3->left->right == NULL);
  destroy_db(db3);

  
  struct node *db4 = create_db("Adam", "1");
  add_item("Curt", "3", &db4, cmp);
  add_item("Berta", "2", &db4, cmp);
  /*This should be balanced 
       A          B
        \   ->   / \
         C      A   C
        /  
       B    
  */
  CU_ASSERT(strcmp(db4->key, "Berta") == 0);  
  CU_ASSERT(strcmp(db4->right->key, "Curt") == 0);
  CU_ASSERT(db4->right->left == NULL);
  CU_ASSERT(db4->right->right == NULL);
  CU_ASSERT(strcmp(db4->left->key, "Adam") == 0);
  CU_ASSERT(db4->left->left == NULL);
  CU_ASSERT(db4->left->right == NULL);
  destroy_db(db4);
  
  
  

  add_item("Bad", "3", NULL, cmp);
}

void testBALANCE(void){
  struct node *db = create_db("A", "1");
  add_item("B", "2", &db, cmp);
  add_item("C", "3", &db, cmp);
  add_item("D", "4", &db, cmp);
  add_item("E", "5", &db, cmp);
  add_item("F", "6", &db, cmp);
  add_item("G", "7", &db, cmp);
  add_item("H", "8", &db, cmp);
  add_item("I", "9", &db, cmp);
  
  void check_order(struct node *db, int **order){
  //inorder traversal
    if (db){
      check_order(db->left, order);
      int tmp = (db->key)[0]-65;
      ((*order)[tmp]) = tmp+1;
      check_order(db->right, order);
    }
  }
 
  int *orderarray = malloc(sizeof(int)*12);

  check_order(db, &orderarray);
  int i;
  for (i = 0; i < 9; ++i){
    CU_ASSERT(orderarray[i] == i+1);
  }
  free(orderarray);

  void check_balance(struct node *db){
    if (db){
      check_balance(db->left);
      if (1 < abs(depth(db->right) - depth(db->left))){
        CU_ASSERT(1 == 0);
      }
      check_balance(db->right);
    }
  }
  check_balance(db);
  destroy_db(db);
}

void testALL_ITEMS(void){
  struct node *db = create_db("A", "1");
  add_item("B", "2", &db, cmp);
  add_item("C", "3", &db, cmp);
  char **item_list = (char**)all_items(db); // ["A","1","B","2","C","3"]
  struct node **first_element = search_entry(*item_list, &db, cmp);
  CU_ASSERT(strcmp((*first_element)->value, *(item_list+1)) == 0);
  remove_item(first_element, &db, cmp);
  free(*item_list);
  free(*(item_list+1));
  
  struct node **second_element = search_entry(*(item_list+2), &db, cmp);
  CU_ASSERT(strcmp((*second_element)->value, *(item_list+3)) == 0);
  remove_item(second_element, &db, cmp);
  free(*(item_list+2));
  free(*(item_list+3));
  
  struct node **third_element = search_entry(*(item_list+4), &db, cmp);
  CU_ASSERT(strcmp((*third_element)->value, *(item_list+5)) == 0);
  remove_item(third_element, &db, cmp);
  free(*(item_list+4));
  free(*(item_list+5));

  CU_ASSERT(db == NULL);
  free(item_list);

  CU_ASSERT(all_items(NULL)==NULL);
}

void testSEARCH_ENTRY(void){
  struct node *db = create_db("A", "1");
  add_item("B", "2", &db, cmp);
  add_item("C", "3", &db, cmp);
  add_item("D", "4", &db, cmp);
  add_item("E", "5", &db, cmp);
  add_item("F", "6", &db, cmp);
  add_item("G", "7", &db, cmp);
  add_item("H", "8", &db, cmp);
  add_item("I", "9", &db, cmp);
  
  struct node **found1 = search_entry("B", &db, cmp); 
  struct node **found2 = search_entry("H", &db, cmp);
  struct node **found3 = search_entry("A", &db, cmp);
  struct node **found4 = search_entry("Q", &db, cmp);
  CU_ASSERT(strcmp((*found1)->value, "2") == 0);
  CU_ASSERT(strcmp((*found2)->value, "8") == 0);
  CU_ASSERT(strcmp((*found3)->value, "1") == 0);
  CU_ASSERT(found4 == NULL);
  destroy_db(db);

  CU_ASSERT(search_entry("Bad", NULL, cmp)==NULL);
}

void testREMOVE_ITEM(void){
  struct node *db = create_db("A", "1");
  add_item("B", "2", &db, cmp);
  add_item("C", "3", &db, cmp);
  add_item("D", "4", &db, cmp);
  add_item("E", "5", &db, cmp);
  add_item("F", "6", &db, cmp);
  add_item("G", "7", &db, cmp);
  add_item("H", "8", &db, cmp);
  add_item("I", "9", &db, cmp);
  
  struct node **found1 = search_entry("D", &db, cmp); 
  struct node **found2 = search_entry("H", &db, cmp);
  struct node **found3 = search_entry("A", &db, cmp);
  remove_item(found1, &db, cmp);
  remove_item(NULL, &db, cmp);

  remove_item(found1, &db, cmp); 
  remove_item(found2, &db, cmp);
  remove_item(found3, &db, cmp);
  CU_ASSERT(search_entry("D", &db, cmp) == NULL);
  CU_ASSERT(search_entry("H", &db, cmp) == NULL);
  CU_ASSERT(search_entry("A", &db, cmp) == NULL);
  remove_item(found1, NULL, cmp);
  remove_item(NULL, NULL, cmp);
  destroy_db(db);
} 

int main()
{
  CU_pSuite pSuite1 = NULL;
  CU_pSuite pSuite2 = NULL;

  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* add a suites to the registry */
  pSuite1 = CU_add_suite("Basic Functions Suite", init_suite_1, clean_suite_1);
  if (NULL == pSuite1)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }
  pSuite2 = CU_add_suite("Advanced Functions Suite", init_suite_2, clean_suite_2);
  if (NULL == pSuite2)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  /* add the tests to the suites */
  /* Basic Functions Suite */
  if (
      (NULL == CU_add_test(pSuite1, "test of create_db()", testCREATE_DB)) ||
      (NULL == CU_add_test(pSuite1, "test of extract_value()", testEXTRACT_VALUE)) ||
      (NULL == CU_add_test(pSuite1, "test of update_value()", testUPDATE_VALUE)) 
      )
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  /* Advanced Functions Suite */
  if (
      (NULL == CU_add_test(pSuite2, "test of add_item()", testADD_ITEM))  ||
      (NULL == CU_add_test(pSuite2, "test of balance invariant", testBALANCE))  ||
      (NULL == CU_add_test(pSuite2, "test of search_entry()", testSEARCH_ENTRY)) ||
      (NULL == CU_add_test(pSuite2, "test of all_items()", testALL_ITEMS)) ||
      (NULL == CU_add_test(pSuite2, "test of remove_item()", testREMOVE_ITEM)) 
      )
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  /* Run all tests using the CUnit Basic interface */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
