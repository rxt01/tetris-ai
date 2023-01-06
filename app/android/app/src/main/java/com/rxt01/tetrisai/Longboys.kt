package com.rxt01.tetrisai

class Longboys:Block() {
    override var grid: MutableList<MutableList<Int>> = mutableListOf(
        mutableListOf(0,0,1,0),
        mutableListOf(0,0,1,0),
        mutableListOf(0,0,1,0),
        mutableListOf(0,0,1,0))

    override fun spin(){
        when(orientation){
            Orientation.UP -> {
                grid = mutableListOf(
                    mutableListOf(0,0,0,0),
                    mutableListOf(0,0,0,0),
                    mutableListOf(1,1,1,1),
                    mutableListOf(0,0,0,0))
                orientation = Orientation.RIGHT
            }
            Orientation.DOWN -> {
                grid = mutableListOf(
                    mutableListOf(0,0,0,0),
                    mutableListOf(1,1,1,1),
                    mutableListOf(0,0,0,0),
                    mutableListOf(0,0,0,0))
                orientation = Orientation.LEFT
            }
            Orientation.LEFT -> {
                grid = mutableListOf(
                    mutableListOf(0,0,1,0),
                    mutableListOf(0,0,1,0),
                    mutableListOf(0,0,1,0),
                    mutableListOf(0,0,1,0))
                orientation = Orientation.UP
            }
            Orientation.RIGHT -> {
                grid = mutableListOf(
                    mutableListOf(0,1,0,0),
                    mutableListOf(0,1,0,0),
                    mutableListOf(0,1,0,0),
                    mutableListOf(0,1,0,0))
                orientation = Orientation.DOWN
            }
        }




    }

}