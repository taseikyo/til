/**
 * @date    2021-01-20 10:25:43
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

package main

import (
	"fmt"
	"sync"
	"time"
)

// WaitGroup 必须通过指针传递给函数
func worker(id int, wg *sync.WaitGroup) {
	// return 时，通知 WaitGroup，当前协程的工作已经完成
	defer wg.Done()

	fmt.Printf("Worker %d starting\n", id)

	time.Sleep(time.Second)
	fmt.Printf("Worker %d done\n", id)
}

func main() {
	// WaitGroup 用于等待该函数启动的所有协程
	var wg sync.WaitGroup

	for i := 1; i <= 5; i++ {
		// 启动几个协程，并为其递增 WaitGroup 的计数器
		wg.Add(1)
		go worker(i, &wg)
	}
	// 阻塞，直到 WaitGroup 计数器恢复为 0；即所有协程的工作都已经完成
	wg.Wait()
}
