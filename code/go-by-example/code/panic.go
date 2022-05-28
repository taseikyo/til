/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2021-01-26 20:01:42
 * @link    github.com/taseikyo
 */

/**
 * panic 意味着有些出乎意料的错误发生
 *
 * 通常我们用它来表示程序正常运行中不应该出现的错误
 * 或者我们不准备优雅处理的错误
 */

package main

import "os"

func main() {

	panic("a problem")

	_, err := os.Create("/tmp/file")
	if err != nil {
		panic(err)
	}
}
