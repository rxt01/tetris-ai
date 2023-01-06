package com.rxt01.tetrisai

class SonOfABitch1:Block() {
    override var grid: MutableList<MutableList<Int>> = mutableListOf(
        mutableListOf(0,0,0,0),
        mutableListOf(0,0,3,0),
        mutableListOf(0,3,3,0),
        mutableListOf(0,3,0,0))

    override fun spin(){
        when(orientation){
            Orientation.UP -> {
                grid = mutableListOf(
                    mutableListOf(0,0,0,0),
                    mutableListOf(0,0,0,0),
                    mutableListOf(0,3,3,0),
                    mutableListOf(0,0,3,3))
                orientation = Orientation.RIGHT
            }
            Orientation.DOWN -> {
                grid = mutableListOf(
                    mutableListOf(0,0,0,0),
                    mutableListOf(0,0,0,0),
                    mutableListOf(0,3,3,0),
                    mutableListOf(0,0,3,3))
                orientation = Orientation.LEFT
            }
            Orientation.LEFT -> {
                grid = mutableListOf(
                    mutableListOf(0,0,0,0),
                    mutableListOf(0,0,3,0),
                    mutableListOf(0,3,3,0),
                    mutableListOf(0,3,0,0))
                orientation = Orientation.UP
            }
            Orientation.RIGHT -> {
                grid = mutableListOf(
                    mutableListOf(0,0,0,0),
                    mutableListOf(0,0,3,0),
                    mutableListOf(0,3,3,0),
                    mutableListOf(0,3,0,0))
                orientation = Orientation.DOWN
            }
        }




    }

}