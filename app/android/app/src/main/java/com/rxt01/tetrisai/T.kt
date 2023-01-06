package com.rxt01.tetrisai

class T:Block() {
    override var grid: MutableList<MutableList<Int>> = mutableListOf(
        mutableListOf(0,0,0,0),
        mutableListOf(0,0,0,0),
        mutableListOf(0,0,7,0),
        mutableListOf(0,7,7,7))

    override fun spin(){
        when(orientation){
            Orientation.UP -> {
                grid = mutableListOf(
                    mutableListOf(0,0,0,0),
                    mutableListOf(0,7,0,0),
                    mutableListOf(0,7,7,0),
                    mutableListOf(0,7,0,0))
                orientation = Orientation.RIGHT
            }
            Orientation.DOWN -> {
                grid = mutableListOf(
                    mutableListOf(0,0,0,0),
                    mutableListOf(0,0,7,0),
                    mutableListOf(0,7,7,0),
                    mutableListOf(0,0,7,0))
                orientation = Orientation.LEFT
            }
            Orientation.LEFT -> {
                grid = mutableListOf(
                    mutableListOf(0,0,0,0),
                    mutableListOf(0,0,0,0),
                    mutableListOf(0,0,7,0),
                    mutableListOf(0,7,7,7))
                orientation = Orientation.UP
            }
            Orientation.RIGHT -> {
                grid = mutableListOf(
                    mutableListOf(0,0,0,0),
                    mutableListOf(0,0,0,0),
                    mutableListOf(0,7,7,7),
                    mutableListOf(0,0,7,0))
                orientation = Orientation.DOWN
            }
        }




    }
}