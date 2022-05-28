/**
 * @date    2021-01-20 09:49:42
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

package main

import (
	"fmt"
	"time"
)

func worker(done chan bool) {
	fmt.Print("working...")
	time.Sleep(time.Second)
	fmt.Println("done")

	done <- true
}

func main() {

	done := make(chan bool, 1)
	go worker(done)
	// 程序将一直阻塞，直至收到 worker 使用通道发送的通知
	//
	// 如果把 <-done 这行代码从程序中移除
	// 程序甚至可能在 worker 开始运行前就结束了
	<-done
}
