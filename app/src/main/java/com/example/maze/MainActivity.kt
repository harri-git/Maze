package com.example.maze

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.KeyEvent
import android.view.View
import android.widget.Button
import android.widget.EditText
import com.example.maze.databinding.ActivityMainBinding
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.MainScope
import kotlinx.coroutines.async
import kotlinx.coroutines.delay
import kotlinx.coroutines.isActive


class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding
    lateinit var button : Button

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        button = findViewById(R.id.button_new_game)
        button.setOnClickListener(listener)

        var job = MainScope().launchPeriodicAsync(100){
            binding.sampleText.text = getMap()
            binding.gameOverText.text = isGameOver()
        }
    }

    fun CoroutineScope.launchPeriodicAsync(
        repeatMillis: Long,
        action: () -> Unit
    ) = this.async {
        if (repeatMillis > 0) {
            while (isActive) {
                action()
                delay(repeatMillis)
            }
        } else {
            action()
        }
    }

    val listener= View.OnClickListener { view ->
        when (view.getId()) {
            R.id.button_new_game -> {
                setMazeSize(12,16)
            }
        }
    }

    override fun onKeyUp(keyCode: Int, event: KeyEvent?): Boolean {

        if (event != null) {
            if (event.getKeyCode() == KeyEvent.KEYCODE_DPAD_DOWN) {
                binding.textViewPoints.setText(moveItem(2).toString())
                return true;
            }
            else if (event.getKeyCode() == KeyEvent.KEYCODE_DPAD_UP){
                binding.textViewPoints.setText(moveItem(1).toString())
                return true;
            }
            else if (event.getKeyCode() == KeyEvent.KEYCODE_DPAD_RIGHT){
                binding.textViewPoints.setText(moveItem(4).toString())
                return true;
            }
            else if (event.getKeyCode() == KeyEvent.KEYCODE_DPAD_LEFT){
                binding.textViewPoints.setText(moveItem(3).toString())
                return true;
            }
        }
        return super.onKeyUp(keyCode, event)
    }

    //native methods
    external fun getMap(): String
    external fun getHighScore(): String
    external fun setMazeSize(width: Int, height: Int)
    external fun moveItem(direction: Int): Int
    external fun isGameOver(): String

    companion object {
        // Used to load the 'maze' library on application startup.
        init {
            System.loadLibrary("maze")
        }
    }

    fun setSize(view: View) {}
}