/**
 * @date    2021-01-20 10:15:50
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

/**
 * 一个非空的通道也是可以关闭的
 * 并且，通道中剩下的值仍然可以被接收到
 */

package main

import "fmt"

func main() {

	queue := make(chan string, 2)
	queue <- "one"
	queue <- "two"
	close(queue)
	// range 迭代从 queue 中得到每个值
	// 因为我们在前面 close 了这个通道，所以，这个迭代会在接收完 2 个值之后结束。
	for elem := range queue {
		fmt.Println(elem)
	}
}
