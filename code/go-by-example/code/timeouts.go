/**
 * @date    2021-01-20 09:54:21
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

/**
 * 使用 select 实现一个超时操作
 *
 * res := <- c1 等待结果，<-Time.After 等待超时（1秒钟）以后发送的值
 * 由于 select 默认处理第一个已准备好的接收操作
 * 因此如果操作耗时超过了允许的 1 秒的话，将会执行超时 case
 */

package main

import (
	"fmt"
	"time"
)

func main() {
	c1 := make(chan string, 1)
	go func() {
		time.Sleep(2 * time.Second)
		c1 <- "result 1"
	}()

	select {
	case res := <-c1:
		fmt.Println(res)
	case <-time.After(1 * time.Second):
		fmt.Println("timeout 1")
	}

	c2 := make(chan string, 1)
	go func() {
		time.Sleep(2 * time.Second)
		c2 <- "result 2"
	}()
	select {
	case res := <-c2:
		fmt.Println(res)
	case <-time.After(3 * time.Second):
		fmt.Println("timeout 2")
	}
}
