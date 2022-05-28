/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2021-01-26 19:59:43
 * @link    github.com/taseikyo
 */

/**
 * 实现了 sort.Interface 接口的 Len、Less 和 Swap 方法
 * 这样我们就可以使用 sort 包的通用 Sort 方法了
 */

package main

import (
	"fmt"
	"sort"
)

type byLength []string

func (s byLength) Len() int {
	return len(s)
}
func (s byLength) Swap(i, j int) {
	s[i], s[j] = s[j], s[i]
}
func (s byLength) Less(i, j int) bool {
	return len(s[i]) < len(s[j])
}

func main() {
	fruits := []string{"peach", "banana", "kiwi"}
	sort.Sort(byLength(fruits))
	fmt.Println(fruits)
}
