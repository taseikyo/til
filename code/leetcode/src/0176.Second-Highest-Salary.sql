/**
 * @date    2020-09-09 19:15:29
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

# Write your MySQL query statement below
select (select distinct salary from Employee order by salary desc limit 1,1) as SecondHighestSalary 


select ifnull((select distinct Salary as SecondHighestSalary
from Employee 
order by SecondHighestSalary desc
limit 1,1),null)as  SecondHighestSalary;