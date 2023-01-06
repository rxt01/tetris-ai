package com.rxt01.tetrisai

class L1:Block() {
    override var grid: MutableList<MutableList<Int>> = mutableListOf(
        mutableListOf(0,0,0,0),
        mutableListOf(0,0,0,0),
        mutableListOf(0,5,0,0),
        mutableListOf(0,5,5,5)
    )

    override fun spin(){
        when(orientation){
            Orientation.UP -> {
                grid = mutableListOf(
                    mutableListOf(0,0,0,0),
                    mutableListOf(0,5,5,0),
                    mutableListOf(0,5,0,0),
                    mutableListOf(0,5,0,0)
                )
                orientation = Orientation.RIGHT
            }
            Orientation.DOWN -> {
                grid = mutableListOf(
                    mutableListOf(0,0,0,0),
                    mutableListOf(0,0,5,0),
                    mutableListOf(0,0,5,0),
                    mutableListOf(0,5,5,0))
                orientation = Orientation.LEFT
            }
            Orientation.LEFT -> {
                grid = mutableListOf(
                    mutableListOf(0,0,0,0),
                    mutableListOf(0,0,0,0),
                    mutableListOf(0,5,0,0),
                    mutableListOf(0,5,5,5))
                orientation = Orientation.UP
            }
            Orientation.RIGHT -> {
                grid = mutableListOf(
                    mutableListOf(0,0,0,0),
                    mutableListOf(0,0,0,0),
                    mutableListOf(0,5,5,5),
                    mutableListOf(0,0,0,5))
                orientation = Orientation.DOWN
            }
        }




    }
}