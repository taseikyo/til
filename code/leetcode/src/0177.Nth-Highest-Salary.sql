/**
 * @date    2020-09-09 19:18:32
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link    github.com/taseikyo
 */

CREATE FUNCTION getNthHighestSalary(N INT) RETURNS INT
BEGIN
  SET N = N-1;
  IF N < 0 THEN
  RETURN NULL;
  ELSE
  RETURN (
      # Write your MySQL query statement below.
      SELECT IFNULL(
          (
          SELECT
          DISTINCT Salary
          FROM Employee
          ORDER BY Salary DESC
          LIMIT N, 1
          ), NULL)
      AS getNthHighestSalary
  );
  END IF;
END
