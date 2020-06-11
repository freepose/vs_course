#define _CRT_SECURE_NO_WARNINGS 1

#include"include\contact.h"

int main()
{
	Filename files;
	initial_filename(&files);
	StudentArray* list = read_students(files.source_contact_file);

	sort_student_by_number(list);
	printf("#(students) = %d\n", list->num_student);
	print_students(list);

	write_student(list, files.target_contact_file);

	return 0;
}

