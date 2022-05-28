/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2021-01-26 19:58:38
 * @link    github.com/taseikyo
 */

/**
 * Go 的 sort 包实现了内建及用户自定义数据类型的排序功能
 */

package main

import (
	"fmt"
	"sort"
)

func main() {

	strs := []string{"c", "a", "b"}
	sort.Strings(strs)
	fmt.Println("Strings:", strs)

	ints := []int{7, 2, 4}
	sort.Ints(ints)
	fmt.Println("Ints:   ", ints)

	s := sort.IntsAreSorted(ints)
	fmt.Println("Sorted: ", s)
}
