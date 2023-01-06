package com.rxt01.tetrisai

class Square:Block() {
    override var grid: MutableList<MutableList<Int>> = mutableListOf(
        mutableListOf(0,0,0,0),
        mutableListOf(0,2,2,0),
        mutableListOf(0,2,2,0),
        mutableListOf(0,0,0,0))

    override fun spin(){
        orientation = when(orientation){
            Orientation.UP -> Orientation.RIGHT

            Orientation.DOWN -> Orientation.LEFT

            Orientation.LEFT -> Orientation.UP

            Orientation.RIGHT -> Orientation.DOWN

        }




    }
}