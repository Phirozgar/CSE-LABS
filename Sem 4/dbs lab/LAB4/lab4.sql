SOURCE FILE LOCATION : "C:\Users\student\Desktop\smallRelationsUniv.sql"




1. Find the number of students in each course. (12 rows)

SELECT COUNT(id) number_of_students, course_id
FROM takes
GROUP BY course_id
ORDER BY number_of_students DESC;



2. Find those departments where the average number of students are greater than 2.

SELECT course_id
FROM takes NATURAL JOIN course
GROUP BY title;

SELECT COUNT(id), dept_name
FROM student
GROUP BY dept_name

SELECT COUNT(id), dept_name
FROM student
GROUP BY dept_name



3. Find the total number of courses in each department. (7 rows)

SELECT COUNT(course_id), dept_name
FROM course
GROUP BY dept_name;



4. Find the names and average salaries of all departments whose average salary is 
greater than 42000. (6 rows)

SELECT dept_name, average_salary
FROM (
	SELECT dept_name, AVG(salary) average_salary
	FROM instructor
	GROUP BY dept_name )
WHERE average_salary > 42000;



5. Find the enrolment of each section that was offered in Spring 2009. (2 rows)

SELECT COUNT(id), course_id
FROM takes 
WHERE year=2009 AND semester='Spring'
GROUP BY sec_id;



6. List all the courses with prerequisite courses, then display course id in increasing 
order. (7 rows)

SELECT DISTINCT(course_id)
FROM prereq
ORDER BY course_id;



7. Display the details of instructors sorting the salary in decreasing order. (12 rows)

SELECT *
FROM instructor
ORDER BY salary DESC;



8. Find the maximum total salary across the departments.

SELECT MAX(salary), dept_name
FROM instructor;


9. Find the average instructors’ salaries of those departments where the average 
salary is greater than 42000.






10. Find the sections that had the maximum enrolment in Spring 2010






11. Find the names of all instructors who teach all students that belong to ‘CSE’ 
department.






12. Find the average salary of those department where the average salary is greater 
than 50000 and total number of instructors in the department are more than 5.





