#define _CRT_SECURE_NO_WARNINGS 1

#include"include\contact.h"



int main()
{
	Filename files;
	initial_filename(&files);
	StudentArray* pArray = read_students(files.source_contact_file);

	sort_student_by_number(pArray);
	printf("#(students) = %d\n", pArray->num_student);
	print_students(pArray);



	return 0;
}