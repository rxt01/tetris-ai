package com.rxt01.tetrisai

class L2:Block() {
    override var grid: MutableList<MutableList<Int>> = mutableListOf(
        mutableListOf(0,0,0,0),
        mutableListOf(0,0,0,0),
        mutableListOf(0,0,0,6),
        mutableListOf(0,6,6,6))

    override fun spin(){
        when(orientation){
            Orientation.UP -> {
                grid = mutableListOf(
                    mutableListOf(0,0,0,0),
                    mutableListOf(0,6,0,0),
                    mutableListOf(0,6,0,0),
                    mutableListOf(0,6,6,0))
                orientation = Orientation.RIGHT
            }
            Orientation.DOWN -> {
                grid = mutableListOf(
                    mutableListOf(0,0,0,0),
                    mutableListOf(0,6,6,0),
                    mutableListOf(0,0,6,0),
                    mutableListOf(0,0,6,0))
                orientation = Orientation.LEFT
            }
            Orientation.LEFT -> {
                grid = mutableListOf(
                    mutableListOf(0,0,0,0),
                    mutableListOf(0,0,0,0),
                    mutableListOf(0,0,0,6),
                    mutableListOf(0,6,6,6))
                orientation = Orientation.UP
            }
            Orientation.RIGHT -> {
                grid = mutableListOf(
                    mutableListOf(0,0,0,0),
                    mutableListOf(0,0,0,0),
                    mutableListOf(0,6,6,6),
                    mutableListOf(0,6,0,0))
                orientation = Orientation.DOWN
            }
        }




    }
}