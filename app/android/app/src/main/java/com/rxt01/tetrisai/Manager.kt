package com.rxt01.tetrisai

import android.util.Log
import java.time.LocalTime
import java.util.LinkedList
import java.util.Queue
import kotlin.random.Random
import kotlin.random.nextInt

class Manager {
    private val list: MutableList<Block> = ArrayList()
    var grid: MutableList<MutableList<Int>> = mutableListOf(
        mutableListOf(0,0,0,0,0,0,0,0,0,0),
        mutableListOf(0,0,0,0,0,0,0,0,0,0),
        mutableListOf(0,0,0,0,0,0,0,0,0,0),
        mutableListOf(0,0,0,0,0,0,0,0,0,0),
        mutableListOf(0,0,0,0,0,0,0,0,0,0),
        mutableListOf(0,0,0,0,0,0,0,0,0,0),
        mutableListOf(0,0,0,0,0,0,0,0,0,0),
        mutableListOf(0,0,0,0,0,0,0,0,0,0),
        mutableListOf(0,0,0,0,0,0,0,0,0,0),
        mutableListOf(0,0,0,0,0,0,0,0,0,0),
        mutableListOf(0,0,0,0,0,0,0,0,0,0),
        mutableListOf(0,0,0,0,0,0,0,0,0,0),
        mutableListOf(0,0,0,0,0,0,0,0,0,0),
        mutableListOf(0,0,0,0,0,0,0,0,0,0),
        mutableListOf(0,0,0,0,0,0,0,0,0,0),
        mutableListOf(0,0,0,0,0,0,0,0,0,0),
        mutableListOf(0,0,0,0,0,0,0,0,0,0),
        mutableListOf(0,0,0,0,0,0,0,0,0,0),
        mutableListOf(0,0,0,0,0,0,0,0,0,0),
        mutableListOf(0,0,0,0,0,0,0,0,0,0)
    )
    fun down(){
        list[list.lastIndex].down(this)
    }
    fun spin(){
        list[list.lastIndex].Spin(this)
    }
    fun left(){
        list[list.lastIndex].left(this)
    }
    fun right(){
        list[list.lastIndex].right(this)
    }
    var score: Long = 0
    private fun delLines(line:Int){
       list.forEachIndexed{index, block ->
           var dif = line - block.y
           if (dif in 0..3){
               list[index].delLine(dif, this)
           }
       }
        list.forEachIndexed { index, block ->
            list[index].down(this)
        }
    }
    fun new(){
        var amount = 0
        for (i in 0..19){
            var delete = true
            for (j in 0..9){
                if (!delete) continue
                if (grid[i][j] == 0){
                    delete = false
                }
            }
            if (delete){
                delLines(i)
                amount++
            }
        }
        score += when(amount){
            1->40
            2->100
            3->300
            4->1200
            else -> 0
        }
        when(nexts.first){
            1->list.add(Longboys())
            2->list.add(Square())
            3->list.add(SonOfABitch1())
            4->list.add(SonOfABitch2())
            5->list.add(L1())
            6->list.add(L2())
            7->list.add(T())
            else->{
                nexts.removeFirst()
                nexts.addLast(Random.nextInt(1..7))
                new()
            }
        }
        nexts.removeFirst()
        nexts3 = LinkedList<Int>()
        nexts3.addLast(nexts[0])
        nexts3.addLast(nexts[1])
        nexts3.addLast(nexts[2])
        list[list.lastIndex].add(this)
    }

    fun Init(){
        for (i in 0..9){
            nexts.addLast(Random.nextInt(1..7))
        }
        new()

    }
    var nexts3: LinkedList<Int> = LinkedList<Int>()
    private var nexts: LinkedList<Int> =LinkedList<Int>()

}