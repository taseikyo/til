/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2021-01-26 20:22:41
 * @link    github.com/taseikyo
 */

package main

import (
	"fmt"
	"time"
)

func main() {

	now := time.Now()
	secs := now.Unix()
	nanos := now.UnixNano()
	fmt.Println(now)
	// UnixMillis 是不存在的，要得到毫秒数的话，手动的从纳秒转化
	millis := nanos / 1000000
	fmt.Println(secs)
	fmt.Println(millis)
	fmt.Println(nanos)

	fmt.Println(time.Unix(secs, 0))
	fmt.Println(time.Unix(0, nanos))
}
