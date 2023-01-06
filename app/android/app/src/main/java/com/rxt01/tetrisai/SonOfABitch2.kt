package com.rxt01.tetrisai

class SonOfABitch2:Block() {
    override var grid: MutableList<MutableList<Int>> = mutableListOf(
        mutableListOf(0,0,0,0),
        mutableListOf(0,4,0,0),
        mutableListOf(0,4,4,0),
        mutableListOf(0,0,4,0))

    override fun spin(){
        when(orientation){
            Orientation.UP -> {
                grid = mutableListOf(
                    mutableListOf(0,0,0,0),
                    mutableListOf(0,0,0,0),
                    mutableListOf(0,4,4,0),
                    mutableListOf(4,4,0,0))
                orientation = Orientation.RIGHT
            }
            Orientation.DOWN -> {
                grid = mutableListOf(
                    mutableListOf(0,0,0,0),
                    mutableListOf(0,0,0,0),
                    mutableListOf(0,4,4,0),
                    mutableListOf(4,4,0,0))
                orientation = Orientation.LEFT
            }
            Orientation.LEFT -> {
                grid = mutableListOf(
                    mutableListOf(0,0,0,0),
                    mutableListOf(0,4,0,0),
                    mutableListOf(0,4,4,0),
                    mutableListOf(0,0,4,0))
                orientation = Orientation.UP
            }
            Orientation.RIGHT -> {
                grid = mutableListOf(
                    mutableListOf(0,0,0,0),
                    mutableListOf(0,4,0,0),
                    mutableListOf(0,4,4,0),
                    mutableListOf(0,0,4,0))
                orientation = Orientation.DOWN
            }
        }




    }
}