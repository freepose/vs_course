#define _CRT_SECURE_NO_WARNINGS 1

#include"include/example_chapter_3.h"
#include"include/example_chapter_4.h"
#include"include/example_chapter_5.h"
#include"include/example_chapter_6.h"
#include"include/example_chapter_7.h"
#include"include/example_chapter_8.h"
#include"include/example_chapter_9.h"

int main()
{
	// chapter 3
	// guess_number();
	// water_charge();
	// odd_or_even();
	// operations();
	// operations_switch();
	// check_triangle();
	// logic_operation();
	// character_counter();

	// chapter 4
	// pi_estimate();
	// sum(100);
	// sum_for(100);
	// printf("%d", fact(5));
	// sum_for_scores();
	// decompose(250);
	// is_prime(4);
	// max_score();
	// sum_of_factorials(100);
	// sum_of_factorials_v1(100);
	// fibonacci(100);
	// data_types();
	// while_test();

	//print_stars(4);
	//print_mulitiplication(9);
	//print_daosanjiao(9);
	//print_deyaosanjiao(9);

	// chapter 5	
	//printf("%.2lf", cylinder(3, 10));
	// printf("%lf", estimate_pi(10e-9));
	// prime_under(100);
	// dectobin(0);

	// chapter 6
	// show_characters();

	// chapter 7

	// printf("%d", heighs_3[1]);	//第二位同学的身高
	// output_average();
	// fibonacci_array();
	// find_array();

	// int a[10] = { 2, 10, 50, 25, 35, 17, 24, 90, 1, 5 };
	// int a[] = { 1, 2, 5, 10, 17, 24, 25, 35, 50, 90 };

	// int x = 35; 
	// printf("a[%d] = %d\n", find(a, N, x), x); // find x and return its index
	// printf("the index of the max value %d\n", max_index(a, N));
	// printf("the index of the min value %d\n", min_index(a, N));
	// print_array(a, 10);
	// select_sort(a, 10);
	// bubble_sort_desc(&a[3], 5);
	// print_array(a, 10);

	//printf("a[%d] = %d", binary_search(a, 10, x), x);
	// yanghui_sanjiaoxing();
	// joseph_loop();

	// array2d_find_max();
	//day_of_year(2020, 4, 16);
	//day_of_year(1900, 4, 16);
	//day_of_year(2000, 4, 16);

	// char_array();

	// chapter 8

	//pointer_as_variable();
	//int a = 2, b = 30;
	//printf("a = %d, b = %d\n", a, b);
	//swap1(&a, &b);
	//printf("a = %d, b = %d\n", a, b);

	//int year = 2020;
	//int day_of_year = 60;
	//int month, day;

	//get_month_day(year, day_of_year, &month, &day);
	//printf("%d-%d-%d", year, month, day);

	//int a[10] = { 2, 10, 50, 25, 35, 17, 24, 90, 1, 5 };

	//// sum of an array
	//printf("sum = %d\n", sum_of_array(a, 10));
	//printf("sum = %d\n", sum_of_array_using_pointer(a, &a[9]));

	// pointer_array_test();
	// show_sizeof_pointers();

	// int array2d[2][3] = { {1, 2, 3}, {4, 5, 6}};
	// print_2d_array(&array2d[0][0], 2, 3);

	// 指针和数组的配合
	// dynamic_allocation_example();
	// dynamic_allocation_2d_array_example();

	// chapter 9
	//Student *pStudents = 0;
	//int n_students = 92;
	//initialize_students(pStudents, n_students);

	Student student = {"201921145006", "易欣雅", 'F', "Guizhou, China",
						95, 98, 99};

	print_a_student(&student);	// 只复制地址4个字节
	// print_a_student_v2(student);	// 复制了sizeof(Student)字节？292 bytes

	// 我们有92个同学：效率对比
	// 4 * 92 vs. 292 * 92：输出效率边忙
	// 为什么感觉不到相差73 * 92倍数：因为计算机运行速度太快了。73 * 92ms, 1 *92ms
	// 当我们要计算10000被

	// 保证：我们每次操作的是同一个对象
	//amend_gender(&student, 'M');
	//print_a_student(&student);
	//amend_gender(&student, 'F');
	average_scores(&student);
	print_a_student(&student);

	// 更容易管理

	return 0;
}
