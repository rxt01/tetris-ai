package com.rxt01.tetrisai

import android.media.AudioManager
import android.media.MediaPlayer
import android.net.Uri
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.os.Handler
import android.provider.MediaStore.Audio.Media
import androidx.core.content.ContentProviderCompat.requireContext
import com.rxt01.tetrisai.databinding.ActivityAiBinding
import com.rxt01.tetrisai.databinding.ActivityPlayBinding
import kotlinx.coroutines.Runnable
import java.io.IOException

class PlayActivity : AppCompatActivity() {
    private lateinit var binding: ActivityPlayBinding
    var mediaPlayer = MediaPlayer()
    var level = 1
    private val manager = Manager()
    private var handler:Handler = Handler()
    var runnable: Runnable? = null
    private var FPS:Long = 60
    private var delay:Long = 1000/FPS
    var framcount = 0

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityPlayBinding.inflate(layoutInflater)
        manager.Init()
        setContentView(binding.root)
        playAudio(level)
        binding.soundToggle.setOnCheckedChangeListener { _, isChecked ->
            if (isChecked){
                playAudio(level)
            }else{
                stopAudio()
            }
        }
        binding.spin.setOnClickListener{
            manager.spin()
        }
        binding.down.setOnClickListener {
            manager.down()
        }
        binding.left.setOnClickListener {
            manager.left()
        }
        binding.right.setOnClickListener {
            manager.right()
        }
        title = "play"
    }

    override fun onResume() {
        handler.postDelayed(Runnable {
            handler.postDelayed(runnable!!, delay)
            if (framcount < getFPT()){
                framcount++
            }else{
                manager.down()
                framcount=0
            }
            level = when(manager.score){
                in 0..100->1
                in 101..500->2
                in 501..1000->3
                in 1001..2000->4
                in 2001..5000->5
                in 5001..10000->6
                in 10001..25000->7
                in 25001..50000->8
                in 50001..100000->9
                in 100001..200000->10
                in 200001..350000->11
                in 350001..500000->12
                in 500001..1000000->13
                in 1000001..5000000->14
                in 5000001..10000000->15
                else -> {16}
            }
            render()

        }.also { runnable=it }, delay)
        super.onResume()
    }

    override fun onPause() {
        super.onPause()
        handler.removeCallbacks(runnable!!)
    }


    private fun playAudio(level: Int) {
        mediaPlayer.stop()
        when(level){
            1,2,3->mediaPlayer.setDataSource(this,Uri.parse("android.resource://"+this.packageName+"/"+R.raw.level1_3))
            4,5,6->mediaPlayer.setDataSource(this,Uri.parse("android.resource://"+this.packageName+"/"+R.raw.level4_6))
            7,8,9->mediaPlayer.setDataSource(this,Uri.parse("android.resource://"+this.packageName+"/"+R.raw.level7_9))
            10,11,12->mediaPlayer.setDataSource(this,Uri.parse("android.resource://"+this.packageName+"/"+R.raw.level10_12))
            13,14,15->mediaPlayer.setDataSource(this,Uri.parse("android.resource://"+this.packageName+"/"+R.raw.level13_15))
            else->mediaPlayer.setDataSource(this,Uri.parse("android.resource://"+this.packageName+"/"+R.raw.infinity))
        }
        mediaPlayer.prepare()
        mediaPlayer.start()

    }
    private fun stopAudio(){
        mediaPlayer.stop()
    }
    private fun getFPT():Long{
        return when(level){
            in 1..3-> 5*FPS
            in 4..6-> 4*FPS
            in 7..9-> 3*FPS
            in 10..12-> 2*FPS
            in 13..15-> FPS
            else->{
                FPS - 10000000/manager.score
            }
        }

    }
    private fun render(){
        binding.g00.setImageResource(getResource(manager.grid[0][0]))
        binding.g01.setImageResource(getResource(manager.grid[0][1]))
        binding.g02.setImageResource(getResource(manager.grid[0][2]))
        binding.g03.setImageResource(getResource(manager.grid[0][3]))
        binding.g04.setImageResource(getResource(manager.grid[0][4]))
        binding.g05.setImageResource(getResource(manager.grid[0][5]))
        binding.g06.setImageResource(getResource(manager.grid[0][6]))
        binding.g07.setImageResource(getResource(manager.grid[0][7]))
        binding.g08.setImageResource(getResource(manager.grid[0][8]))
        binding.g09.setImageResource(getResource(manager.grid[0][9]))
        binding.g10.setImageResource(getResource(manager.grid[1][0]))
        binding.g11.setImageResource(getResource(manager.grid[1][1]))
        binding.g12.setImageResource(getResource(manager.grid[1][2]))
        binding.g13.setImageResource(getResource(manager.grid[1][3]))
        binding.g14.setImageResource(getResource(manager.grid[1][4]))
        binding.g15.setImageResource(getResource(manager.grid[1][5]))
        binding.g16.setImageResource(getResource(manager.grid[1][6]))
        binding.g17.setImageResource(getResource(manager.grid[1][7]))
        binding.g18.setImageResource(getResource(manager.grid[1][8]))
        binding.g19.setImageResource(getResource(manager.grid[1][9]))
        binding.g20.setImageResource(getResource(manager.grid[2][0]))
        binding.g21.setImageResource(getResource(manager.grid[2][1]))
        binding.g22.setImageResource(getResource(manager.grid[2][2]))
        binding.g23.setImageResource(getResource(manager.grid[2][3]))
        binding.g24.setImageResource(getResource(manager.grid[2][4]))
        binding.g25.setImageResource(getResource(manager.grid[2][5]))
        binding.g26.setImageResource(getResource(manager.grid[2][6]))
        binding.g27.setImageResource(getResource(manager.grid[2][7]))
        binding.g28.setImageResource(getResource(manager.grid[2][8]))
        binding.g29.setImageResource(getResource(manager.grid[2][9]))
        binding.g30.setImageResource(getResource(manager.grid[3][0]))
        binding.g31.setImageResource(getResource(manager.grid[3][1]))
        binding.g32.setImageResource(getResource(manager.grid[3][2]))
        binding.g33.setImageResource(getResource(manager.grid[3][3]))
        binding.g34.setImageResource(getResource(manager.grid[3][4]))
        binding.g35.setImageResource(getResource(manager.grid[3][5]))
        binding.g36.setImageResource(getResource(manager.grid[3][6]))
        binding.g37.setImageResource(getResource(manager.grid[3][7]))
        binding.g38.setImageResource(getResource(manager.grid[3][8]))
        binding.g39.setImageResource(getResource(manager.grid[3][9]))
        binding.g40.setImageResource(getResource(manager.grid[4][0]))
        binding.g41.setImageResource(getResource(manager.grid[4][1]))
        binding.g42.setImageResource(getResource(manager.grid[4][2]))
        binding.g43.setImageResource(getResource(manager.grid[4][3]))
        binding.g44.setImageResource(getResource(manager.grid[4][4]))
        binding.g45.setImageResource(getResource(manager.grid[4][5]))
        binding.g46.setImageResource(getResource(manager.grid[4][6]))
        binding.g47.setImageResource(getResource(manager.grid[4][7]))
        binding.g48.setImageResource(getResource(manager.grid[4][8]))
        binding.g49.setImageResource(getResource(manager.grid[4][9]))
        binding.g50.setImageResource(getResource(manager.grid[5][0]))
        binding.g51.setImageResource(getResource(manager.grid[5][1]))
        binding.g52.setImageResource(getResource(manager.grid[5][2]))
        binding.g53.setImageResource(getResource(manager.grid[5][3]))
        binding.g54.setImageResource(getResource(manager.grid[5][4]))
        binding.g55.setImageResource(getResource(manager.grid[5][5]))
        binding.g56.setImageResource(getResource(manager.grid[5][6]))
        binding.g57.setImageResource(getResource(manager.grid[5][7]))
        binding.g58.setImageResource(getResource(manager.grid[5][8]))
        binding.g59.setImageResource(getResource(manager.grid[5][9]))
        binding.g60.setImageResource(getResource(manager.grid[6][0]))
        binding.g61.setImageResource(getResource(manager.grid[6][1]))
        binding.g62.setImageResource(getResource(manager.grid[6][2]))
        binding.g63.setImageResource(getResource(manager.grid[6][3]))
        binding.g64.setImageResource(getResource(manager.grid[6][4]))
        binding.g65.setImageResource(getResource(manager.grid[6][5]))
        binding.g66.setImageResource(getResource(manager.grid[6][6]))
        binding.g67.setImageResource(getResource(manager.grid[6][7]))
        binding.g68.setImageResource(getResource(manager.grid[6][8]))
        binding.g69.setImageResource(getResource(manager.grid[6][9]))
        binding.g70.setImageResource(getResource(manager.grid[7][0]))
        binding.g71.setImageResource(getResource(manager.grid[7][1]))
        binding.g72.setImageResource(getResource(manager.grid[7][2]))
        binding.g73.setImageResource(getResource(manager.grid[7][3]))
        binding.g74.setImageResource(getResource(manager.grid[7][4]))
        binding.g75.setImageResource(getResource(manager.grid[7][5]))
        binding.g76.setImageResource(getResource(manager.grid[7][6]))
        binding.g77.setImageResource(getResource(manager.grid[7][7]))
        binding.g78.setImageResource(getResource(manager.grid[7][8]))
        binding.g79.setImageResource(getResource(manager.grid[7][9]))
        binding.g80.setImageResource(getResource(manager.grid[8][0]))
        binding.g81.setImageResource(getResource(manager.grid[8][1]))
        binding.g82.setImageResource(getResource(manager.grid[8][2]))
        binding.g83.setImageResource(getResource(manager.grid[8][3]))
        binding.g84.setImageResource(getResource(manager.grid[8][4]))
        binding.g85.setImageResource(getResource(manager.grid[8][5]))
        binding.g86.setImageResource(getResource(manager.grid[8][6]))
        binding.g87.setImageResource(getResource(manager.grid[8][7]))
        binding.g88.setImageResource(getResource(manager.grid[8][8]))
        binding.g89.setImageResource(getResource(manager.grid[8][9]))
        binding.g90.setImageResource(getResource(manager.grid[9][0]))
        binding.g91.setImageResource(getResource(manager.grid[9][1]))
        binding.g92.setImageResource(getResource(manager.grid[9][2]))
        binding.g93.setImageResource(getResource(manager.grid[9][3]))
        binding.g94.setImageResource(getResource(manager.grid[9][4]))
        binding.g95.setImageResource(getResource(manager.grid[9][5]))
        binding.g96.setImageResource(getResource(manager.grid[9][6]))
        binding.g97.setImageResource(getResource(manager.grid[9][7]))
        binding.g98.setImageResource(getResource(manager.grid[9][8]))
        binding.g99.setImageResource(getResource(manager.grid[9][9]))
        binding.g100.setImageResource(getResource(manager.grid[10][0]))
        binding.g101.setImageResource(getResource(manager.grid[10][1]))
        binding.g102.setImageResource(getResource(manager.grid[10][2]))
        binding.g103.setImageResource(getResource(manager.grid[10][3]))
        binding.g104.setImageResource(getResource(manager.grid[10][4]))
        binding.g105.setImageResource(getResource(manager.grid[10][5]))
        binding.g106.setImageResource(getResource(manager.grid[10][6]))
        binding.g107.setImageResource(getResource(manager.grid[10][7]))
        binding.g108.setImageResource(getResource(manager.grid[10][8]))
        binding.g109.setImageResource(getResource(manager.grid[10][9]))
        binding.g110.setImageResource(getResource(manager.grid[11][0]))
        binding.g111.setImageResource(getResource(manager.grid[11][1]))
        binding.g112.setImageResource(getResource(manager.grid[11][2]))
        binding.g113.setImageResource(getResource(manager.grid[11][3]))
        binding.g114.setImageResource(getResource(manager.grid[11][4]))
        binding.g115.setImageResource(getResource(manager.grid[11][5]))
        binding.g116.setImageResource(getResource(manager.grid[11][6]))
        binding.g117.setImageResource(getResource(manager.grid[11][7]))
        binding.g118.setImageResource(getResource(manager.grid[11][8]))
        binding.g119.setImageResource(getResource(manager.grid[11][9]))
        binding.g120.setImageResource(getResource(manager.grid[12][0]))
        binding.g121.setImageResource(getResource(manager.grid[12][1]))
        binding.g122.setImageResource(getResource(manager.grid[12][2]))
        binding.g123.setImageResource(getResource(manager.grid[12][3]))
        binding.g124.setImageResource(getResource(manager.grid[12][4]))
        binding.g125.setImageResource(getResource(manager.grid[12][5]))
        binding.g126.setImageResource(getResource(manager.grid[12][6]))
        binding.g127.setImageResource(getResource(manager.grid[12][7]))
        binding.g128.setImageResource(getResource(manager.grid[12][8]))
        binding.g129.setImageResource(getResource(manager.grid[12][9]))
        binding.g130.setImageResource(getResource(manager.grid[13][0]))
        binding.g131.setImageResource(getResource(manager.grid[13][1]))
        binding.g132.setImageResource(getResource(manager.grid[13][2]))
        binding.g133.setImageResource(getResource(manager.grid[13][3]))
        binding.g134.setImageResource(getResource(manager.grid[13][4]))
        binding.g135.setImageResource(getResource(manager.grid[13][5]))
        binding.g136.setImageResource(getResource(manager.grid[13][6]))
        binding.g137.setImageResource(getResource(manager.grid[13][7]))
        binding.g138.setImageResource(getResource(manager.grid[13][8]))
        binding.g139.setImageResource(getResource(manager.grid[13][9]))
        binding.g140.setImageResource(getResource(manager.grid[14][0]))
        binding.g141.setImageResource(getResource(manager.grid[14][1]))
        binding.g142.setImageResource(getResource(manager.grid[14][2]))
        binding.g143.setImageResource(getResource(manager.grid[14][3]))
        binding.g144.setImageResource(getResource(manager.grid[14][4]))
        binding.g145.setImageResource(getResource(manager.grid[14][5]))
        binding.g146.setImageResource(getResource(manager.grid[14][6]))
        binding.g147.setImageResource(getResource(manager.grid[14][7]))
        binding.g148.setImageResource(getResource(manager.grid[14][8]))
        binding.g149.setImageResource(getResource(manager.grid[14][9]))
        binding.g150.setImageResource(getResource(manager.grid[15][0]))
        binding.g151.setImageResource(getResource(manager.grid[15][1]))
        binding.g152.setImageResource(getResource(manager.grid[15][2]))
        binding.g153.setImageResource(getResource(manager.grid[15][3]))
        binding.g154.setImageResource(getResource(manager.grid[15][4]))
        binding.g155.setImageResource(getResource(manager.grid[15][5]))
        binding.g156.setImageResource(getResource(manager.grid[15][6]))
        binding.g157.setImageResource(getResource(manager.grid[15][7]))
        binding.g158.setImageResource(getResource(manager.grid[15][8]))
        binding.g159.setImageResource(getResource(manager.grid[15][9]))
        binding.g160.setImageResource(getResource(manager.grid[16][0]))
        binding.g161.setImageResource(getResource(manager.grid[16][1]))
        binding.g162.setImageResource(getResource(manager.grid[16][2]))
        binding.g163.setImageResource(getResource(manager.grid[16][3]))
        binding.g164.setImageResource(getResource(manager.grid[16][4]))
        binding.g165.setImageResource(getResource(manager.grid[16][5]))
        binding.g166.setImageResource(getResource(manager.grid[16][6]))
        binding.g167.setImageResource(getResource(manager.grid[16][7]))
        binding.g168.setImageResource(getResource(manager.grid[16][8]))
        binding.g169.setImageResource(getResource(manager.grid[16][9]))
        binding.g170.setImageResource(getResource(manager.grid[17][0]))
        binding.g171.setImageResource(getResource(manager.grid[17][1]))
        binding.g172.setImageResource(getResource(manager.grid[17][2]))
        binding.g173.setImageResource(getResource(manager.grid[17][3]))
        binding.g174.setImageResource(getResource(manager.grid[17][4]))
        binding.g175.setImageResource(getResource(manager.grid[17][5]))
        binding.g176.setImageResource(getResource(manager.grid[17][6]))
        binding.g177.setImageResource(getResource(manager.grid[17][7]))
        binding.g178.setImageResource(getResource(manager.grid[17][8]))
        binding.g179.setImageResource(getResource(manager.grid[17][9]))
        binding.g180.setImageResource(getResource(manager.grid[18][0]))
        binding.g181.setImageResource(getResource(manager.grid[18][1]))
        binding.g182.setImageResource(getResource(manager.grid[18][2]))
        binding.g183.setImageResource(getResource(manager.grid[18][3]))
        binding.g184.setImageResource(getResource(manager.grid[18][4]))
        binding.g185.setImageResource(getResource(manager.grid[18][5]))
        binding.g186.setImageResource(getResource(manager.grid[18][6]))
        binding.g187.setImageResource(getResource(manager.grid[18][7]))
        binding.g188.setImageResource(getResource(manager.grid[18][8]))
        binding.g189.setImageResource(getResource(manager.grid[18][9]))
        binding.g190.setImageResource(getResource(manager.grid[19][0]))
        binding.g191.setImageResource(getResource(manager.grid[19][1]))
        binding.g192.setImageResource(getResource(manager.grid[19][2]))
        binding.g193.setImageResource(getResource(manager.grid[19][3]))
        binding.g194.setImageResource(getResource(manager.grid[19][4]))
        binding.g195.setImageResource(getResource(manager.grid[19][5]))
        binding.g196.setImageResource(getResource(manager.grid[19][6]))
        binding.g197.setImageResource(getResource(manager.grid[19][7]))
        binding.g198.setImageResource(getResource(manager.grid[19][8]))
        binding.g199.setImageResource(getResource(manager.grid[19][9]))
        binding.textscore.text = "score:${manager.score}"

    }
    private fun getResource(num:Int): Int {
        return when(num){
            1->R.mipmap.longboy_foreground
            2->R.mipmap.block_foreground
            3->R.mipmap.z1_foreground
            4->R.mipmap.z2_foreground
            5->R.mipmap.l1_foreground
            6->R.mipmap.l2_foreground
            7->R.mipmap.t_foreground
            else->R.mipmap.empty_foreground
        }
    }
}