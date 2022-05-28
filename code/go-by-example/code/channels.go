/**
 * @date    2021-01-20 09:47:40
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

/**
 * 使用 make(chan val-type) 创建一个新的通道
 *
 * 使用 channel <- 语法 发送 一个新的值到通道中
 * 使用 <-channel 语法从通道中 接收 一个值
 */

package main

import "fmt"

func main() {
	messages := make(chan string)

	go func() { messages <- "ping" }()

	msg := <-messages
	fmt.Println(msg)
}
