/**
 * @date    2021-01-20 09:52:43
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

/**
 * 选择器（select） 让你可以同时等待多个通道操作
 * 将协程、通道和选择器结合，是 Go 的一个强大特性
 */

package main

import (
	"fmt"
	"time"
)

func main() {

	c1 := make(chan string)
	c2 := make(chan string)

	go func() {
		time.Sleep(1 * time.Second)
		c1 <- "one"
	}()
	go func() {
		time.Sleep(2 * time.Second)
		c2 <- "two"
	}()

	for i := 0; i < 2; i++ {
		select {
		case msg1 := <-c1:
			fmt.Println("received", msg1)
		case msg2 := <-c2:
			fmt.Println("received", msg2)
		}
	}
}

// 程序总共仅运行了两秒左右
// 因为 1 秒 和 2 秒的 Sleeps 是并发执行的
