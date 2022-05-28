/**
 * @date    2021-01-19 16:08:05
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

/**
 * 我们调用 intSeq 函数，将返回值（一个函数）赋给 nextInt。
 * 这个函数的值包含了自己的值 i，这样在每次调用 nextInt 时，
 * 都会更新 i 的值。
 */

package main

import "fmt"

func intSeq() func() int {
	i := 0
	return func() int {
		i++
		return i
	}
}

func main() {
	nextInt := intSeq()

	fmt.Println(nextInt())
	fmt.Println(nextInt())
	fmt.Println(nextInt())

	newInts := intSeq()
	fmt.Println(newInts())
}
