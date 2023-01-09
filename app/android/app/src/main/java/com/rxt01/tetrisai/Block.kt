package com.rxt01.tetrisai

import android.util.Log

abstract class Block{
    abstract var grid: MutableList<MutableList<Int>>
    //need to change the implementations such that the pieces spin the correct way
    abstract fun spin()
    open var orientation:Orientation = Orientation.UP
    open var x:Int =3
    open var y:Int =0
    open var settled=false
    open fun delLine(num:Int, manager: Manager){
        remove(manager)
        if (num > 0){
            for (i in (num - 1) downTo 0){
                grid[i+1]=grid[i]
            }
        }
        grid[0]= mutableListOf(0,0,0,0)

        add(manager)
    }
    open fun remove(manager: Manager){
        for (i in grid.indices){
            for (j in grid[i].indices){
                if (grid[i][j] != 0){
                    manager.grid[i+y][j+x] = 0
                }
            }
        }
    }
    open fun add(manager: Manager){
        for (i in grid.indices){
            for (j in grid[i].indices){
                if (grid[i][j] != 0){
                    manager.grid[i+y][j+x] = grid[i][j]
                }
            }
        }
    }
    open fun Spin(manager: Manager){
        remove(manager)
        val Grid = grid
        val Orient = orientation
        spin()
        if(!check(manager)){
            grid = Grid
            orientation = Orient
        }
        add(manager)
    }
    open fun check(manager: Manager): Boolean {
        for (i in grid.indices){
            for (j in grid[i].indices){
                if (grid[i][j] != 0){
                    if (i+y<0 || 19<i+y || j+x<0||9<j+x|| manager.grid[i+y][j+x] !=0){
                        return false
                    }
                }
            }
        }
        return true
    }
    open fun left(manager: Manager){
        remove(manager)
        x--
        if(!check(manager))x++
        add(manager)
    }
    open fun right(manager: Manager){
        remove(manager)
        x++
        if(!check(manager))x--
        add(manager)
    }
    open fun down(manager: Manager){
        remove(manager)
        y++
        if(!check(manager)){
            y--

            if(!settled){
                settled = true
                add(manager)
                manager.new()
                return
            }
        }
        add(manager)

    }
}