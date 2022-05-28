/**
 * @date    2021-01-19 16:05:36
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

/**
 * 变参函数使用常规的调用方式，传入独立的参数
 * 如果你有一个含有多个值的 slice，想把它们作为参数使用，
 * 你需要这样调用 func(slice...)
 */

package main

import "fmt"

func sum(nums ...int) {
	fmt.Print(nums, " ")
	total := 0
	for _, num := range nums {
		total += num
	}
	fmt.Println(total)
}

func main() {
	sum(1, 2)
	sum(1, 2, 3)

	nums := []int{1, 2, 3, 4}
	sum(nums...)
}
