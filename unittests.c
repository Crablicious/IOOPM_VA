#include <string.h>
#include "CUnit/Basic.h"
#include <stdlib.h>
#include "db_test.h"

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


void testCREATE_NODE(void){
  struct node *first_node = create_node("First", "1");
  struct node *second_node = create_node("Second", "2");
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
  struct node *first_node = create_node("First", "1");
  struct node *second_node = create_node("Second", "");
  struct node *third_node = create_node("Third", "Hej Hopp");
  CU_ASSERT(strcmp(extract_value(first_node), first_node->value) == 0);
  CU_ASSERT(strcmp(extract_value(second_node), second_node->value) == 0);
  CU_ASSERT(strcmp(extract_value(third_node), third_node->value) == 0);
  destroy(&first_node);
  destroy(&second_node);
  destroy(&third_node);
}

void testUPDATE_VALUE(void){
  struct node *first_node = create_node("First", "1");
  struct node *second_node = create_node("Second", "");
  struct node *third_node = create_node("Third", "Hej Hopp");
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

void testADD_NODE(void){
  struct node *db = create_node("Adam", "1");
  add_node("Berta", "2", &db);
  add_node("Curt", "3", &db);
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
  destroy_tree(db);
  
  struct node *db2 = create_node("Curt", "3");
  add_node("Berta", "2", &db2);
  add_node("Adam", "1", &db2);
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
  destroy_tree(db2);

  struct node *db3 = create_node("Curt", "3");
  add_node("Adam", "1", &db3);
  add_node("Berta", "2", &db3);
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
  destroy_tree(db3);

  
  struct node *db4 = create_node("Adam", "1");
  add_node("Curt", "3", &db4);
  add_node("Berta", "2", &db4);
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
  destroy_tree(db4);
  
  
  struct node *db5 = create_node("A", "1");
  add_node("B", "2", &db5);
  add_node("C", "3", &db5);
  add_node("D", "4", &db5);
  add_node("E", "5", &db5);
  add_node("F", "6", &db5);
  add_node("G", "7", &db5);
  add_node("H", "8", &db5);
  add_node("I", "9", &db5);
  
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

  check_order(db5, &orderarray);
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
  check_balance(db5);
  destroy_tree(db5);
}


void testSEARCH_ENTRY(void){
  struct node *db = create_node("A", "1");
  add_node("B", "2", &db);
  add_node("C", "3", &db);
  add_node("D", "4", &db);
  add_node("E", "5", &db);
  add_node("F", "6", &db);
  add_node("G", "7", &db);
  add_node("H", "8", &db);
  add_node("I", "9", &db);
  
  struct node **found1 = search_entry("B", &db); 
  struct node **found2 = search_entry("H", &db);
  struct node **found3 = search_entry("A", &db);
  struct node **found4 = search_entry("Q", &db);
  CU_ASSERT(strcmp((*found1)->value, "2") == 0);
  CU_ASSERT(strcmp((*found2)->value, "8") == 0);
  CU_ASSERT(strcmp((*found3)->value, "1") == 0);
  CU_ASSERT(found4 == NULL);
  destroy_tree(db);
}

void testREMOVE_NODE(void){
  struct node *db = create_node("A", "1");
  add_node("B", "2", &db);
  add_node("C", "3", &db);
  add_node("D", "4", &db);
  add_node("E", "5", &db);
  add_node("F", "6", &db);
  add_node("G", "7", &db);
  add_node("H", "8", &db);
  add_node("I", "9", &db);
  
  struct node **found1 = search_entry("D", &db); 
  struct node **found2 = search_entry("H", &db);
  struct node **found3 = search_entry("A", &db);
  remove_node(found1, &db);
  remove_node(found2, &db);
  remove_node(found3, &db);
  CU_ASSERT(search_entry("D", &db) == NULL);
  CU_ASSERT(search_entry("H", &db) == NULL);
  CU_ASSERT(search_entry("A", &db) == NULL);
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
      (NULL == CU_add_test(pSuite1, "test of create_node()", testCREATE_NODE)) ||
      (NULL == CU_add_test(pSuite1, "test of extract_value()", testEXTRACT_VALUE)) ||
      (NULL == CU_add_test(pSuite1, "test of update_value()", testUPDATE_VALUE)) 
      )
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  /* Advanced Functions Suite */
  if (
      (NULL == CU_add_test(pSuite2, "test of add_node()", testADD_NODE))  ||
      (NULL == CU_add_test(pSuite2, "test of search_entry()", testSEARCH_ENTRY)) ||
       (NULL == CU_add_test(pSuite2, "test of remove_node()", testREMOVE_NODE)) 
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
