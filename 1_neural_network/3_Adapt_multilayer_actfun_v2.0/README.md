
本次程序将公式中的偏导部分，采用偏导的定义进行代码上的分解。即： <br>
gradient = (f(x+delta_x)-f(x))/delta_x      delta_x --> 0 <br>
省去了多种激活函数，任意层数，公式推导之间的计算， <br>
使得代码的适用范围大大增加          &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;    --------qiuyang.duan<br>


# architecture #
![architecture](https://github.com/depthyang/maching_learning/raw/master/Picture/BP_multi-layer_feedforward_neural.png)

使用方法<br>
  先编译 <br>  make all<br>
  然后执行<br> ./myneural<br>
  如果没有好的选择，可以参考下边的参数<br>
pls input number of input_node:2<br>
pls input number of output_node:2<br>
pls input number of hidden layer:2<br>
pls input 2_layer_node_num:3<br>
pls input 3_layer_node_num:3<br>
