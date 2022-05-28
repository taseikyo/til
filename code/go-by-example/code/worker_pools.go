/**
 * @date    2021-01-20 10:21:49
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

package main

import (
	"fmt"
	"time"
)

// worker 将在 jobs 频道上接收工作，并在 results 上发送相应的结果
// 每个 worker 我们都会 sleep 一秒钟，以模拟一项昂贵的（耗时一秒钟的）任务
func worker(id int, jobs <-chan int, results chan<- int) {
	for j := range jobs {
		fmt.Println("worker", id, "started  job", j)
		time.Sleep(time.Second)
		fmt.Println("worker", id, "finished job", j)
		results <- j * 2
	}
}

func main() {
	const numJobs = 5
	jobs := make(chan int, numJobs)
	results := make(chan int, numJobs)
	// 启动了 3 个 worker，初始是阻塞的，因为还没有传递任务
	for w := 1; w <= 3; w++ {
		go worker(w, jobs, results)
	}
	// 发送 5 个 jobs， 然后 close 这些通道，表示这些就是所有的任务了
	for j := 1; j <= numJobs; j++ {
		jobs <- j
	}
	close(jobs)
	// 最后，我们收集所有这些任务的返回值
	// 这也确保了所有的 worker 协程都已完成
	// 另一个等待多个协程的方法是使用 WaitGroup
	for a := 1; a <= numJobs; a++ {
		<-results
	}
}
