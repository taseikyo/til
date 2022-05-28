/**
 * @date    2021-01-19 15:44:19
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

/**
 * 数值型常量没有确定的类型，直到被给定某个类型，比如显式类型转化。
 * 一个数字可以根据上下文的需要（比如变量赋值、函数调用）自动确定类型。
 * 举个例子，这里的 math.Sin 函数需要一个 float64 的参数，n 会自动确定类型。
 */

package main

import (
	"fmt"
	"math"
)

const s string = "constant"

func main() {
	fmt.Println(s)

	const n = 500000000

	const d = 3e20 / n
	fmt.Println(d)

	fmt.Println(int64(d))

	fmt.Println(math.Sin(n))
}
