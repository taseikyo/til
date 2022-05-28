/**
 * @date    2021-01-20 10:12:50
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

/**
 * 在工作协程中，使用 j, more := <- jobs 循环的从 jobs 接收数据
 * 根据接收的第二个值，如果 jobs 已经关闭了
 * 并且通道中所有的值都已经接收完毕，那么 more 的值将是 false
 *
 * 当我们完成所有的任务时，会使用这个特性通过 done 通道通知 main 协程
 */

package main

import "fmt"

func main() {
	jobs := make(chan int, 5)
	done := make(chan bool)

	go func() {
		for {
			j, more := <-jobs
			if more {
				fmt.Println("received job", j)
			} else {
				fmt.Println("received all jobs")
				done <- true
				return
			}
		}
	}()

	for j := 1; j <= 3; j++ {
		jobs <- j
		fmt.Println("sent job", j)
	}
	close(jobs)
	fmt.Println("sent all jobs")
	// 使用前面学到的通道同步方法等待任务结束
	<-done
}
