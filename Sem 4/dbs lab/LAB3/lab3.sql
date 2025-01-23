SELECT * FROM student;

1. Find courses that ran in Fall 2009 or in Spring 2010
SELECT course_id
FROM section
WHERE semester = 'Spring' AND year = 2010
UNION
SELECT course_id
FROM section
WHERE semester = 'Fall' AND year = 2009;


2. Find courses that ran in Fall 2009 and in spring 2010
SELECT course_id
FROM section
WHERE semester = 'Spring' AND year = 2010
INTERSECT
SELECT course_id
FROM section
WHERE semester = 'Fall' AND year = 2009;


3. Find courses that ran in Fall 2009 but not in Spring 2010
SELECT course_id
FROM section
WHERE semester = 'Fall' AND year = 2009
MINUS
SELECT course_id
FROM section
WHERE semester = 'Spring' AND year = 2010;

4. Find the name of the course for which none of the students registered.
SELECT title
FROM course
WHERE course.course_id IN (
	SELECT course_id
	FROM course
	MINUS
	SELECT course_id
	FROM takes
	);

5. Find courses offered in Fall 2009 and in Spring 2010. (USING IN / NOT IN)
SELECT DISTINCT course_id
FROM takes
WHERE semester='Fall' AND year=2009 AND course_id IN (
	SELECT course_id
	FROM takes
	WHERE semester='Spring' AND year=2010
	);

6. Find the total number of students who have taken course taught by the instructor 
with ID 10101.
SELECT COUNT(DISTINCT id)
FROM takes
WHERE (course_id, sec_id, semester, year) IN (
	SELECT course_id, sec_id, semester, year
	FROM teaches
	WHERE id = 10101
	);

7. Find courses offered in Fall 2009 but not in Spring 2010.
SELECT DISTINCT course_id
FROM takes
WHERE semester='Fall' AND year=2009 AND course_id NOT IN (
	SELECT course_id
	FROM takes
	WHERE semester='Spring' AND year=2010
	);

8. Find the names of all students whose name is same as the instructor’s name.
SELECT student.name
FROM student, instructor
WHERE student.name = instructor.name;

9. Find names of instructors with salary greater than that of some (at least one) instructor
in the Biology department.
SELECT name
FROM instructor
WHERE salary > SOME(
	SELECT salary
	FROM instructor
	WHERE dept_name = 'Biology'
	);

10. Find the names of all instructors whose salary is greater than the salary of all 
instructors in the Biology department.
SELECT name
FROM instructor
WHERE salary > ALL(
	SELECT salary
	FROM instructor
	WHERE dept_name = 'Biology'
	);

11. Find the departments that have the highest average salary.
SELECT MAX(AVG(salary)) highest_salary
FROM instructor
GROUP BY dept_name;

12. Find the names of those departments whose budget is lesser than the average salary 
of all instructors.
SELECT dept_name
FROM department
WHERE budget < (
	SELECT ROUND(AVG(salary), 2) 
	FROM instructor
	);

13. Find all courses taught in both the Fall 2009 semester and in the Spring 2010 semester.
SELECT DISTINCT course_id
FROM takes t
WHERE EXISTS(
	SELECT course_id
	FROM section s
	WHERE semester = 'Spring' AND year = 2010 AND s.course_id = t.course_id
	INTERSECT
	SELECT course_id
	FROM section s
	WHERE semester = 'Fall' AND year = 2009 AND s.course_id = t.course_id
	);

14. Find all students who have taken all courses offered in the Biology department
SELECT t.id 
FROM takes t, course c
WHERE (
	SELECT COUNT(t.id) 
	FROM takes t, course c
	WHERE t.course_id = c.course_id AND dept_name = 'Biology'
	GROUP BY t.id
	) > (
	SELECT COUNT(course_id)
	FROM course 
	WHERE dept_name = 'Biology'
	);

15. Find all courses that were offered at most once in 2009.
SELECT title
FROM course c, section s
WHERE c.course_id = s.course_id AND 
