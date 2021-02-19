7109056193 梁維中
無線網路效能分析期末作業，針對M/M/s/K及M/G/1的效能分析。 

我會針對M/M/s/k和M/G/1/∞進行模擬與數學分析，因為G/M/m/∞無法在G採uniform distribution的情境進行數學分析，所以這個部分只有製作模擬。
因為要與M/G/1進行比對的關係，對於三個實驗的server數量都設置為1、queue的長度都設為無窮大、μ設置為6.0、模擬時抵達的顧客的總量為200,000。

可以看到，我製作的模擬與數學分析是非常接近的，唯M/M/1在λ上升到5.5的時候，與實際會產生約10%的誤差。
關於誤差，我想有一小部份是因為我的數學使用M/M/s/k的公式，並將k設置成了顧客的總量（而不是使用M/M/s/∞的公式），但大部分應該都是實驗的誤差。
根據自己製作μ=8.0且λ=7.5的數據結果，誤差值應該取決於λ與μ的差距，當他們的差距達到0.5的時候，也是產生約10%的誤差。λ與μ愈接近，誤差應該就會越大。
對於M/G/1的模擬，與數學曲線幾乎是重合的，這應該可以證明我的模擬是非常準確的。
可以看到，根據實驗顯示，λ愈大，對於服務時間採用uniform distribution的M/G/1模型看起來是更有利的。服務時間使用exponential distribution產生的M/M/1和G/M/1模型更可能會有人佔用長的服務時間，導致在整個系統裡面整體等待的時間上升。
![image]https://github.com/thumbd78492/MMSK_QueueingModel_Analysis/blob/main/pics/lambda_Ls.png
![image]https://github.com/thumbd78492/MMSK_QueueingModel_Analysis/blob/main/pics/lambda_Lq.png
![image]https://github.com/thumbd78492/MMSK_QueueingModel_Analysis/blob/main/pics/lambda_Ws.png
![image]https://github.com/thumbd78492/MMSK_QueueingModel_Analysis/blob/main/pics/lambda_Wq.png
  
   
接著是固定λ為2.0，其餘條件不變的分析。
可以看到，當μ與λ的距離足夠大（在這個例子裡，當μ=2.5,λ=2.0時，看起來0.5的差值就已經足夠大了）的時候，我模擬跟數學分析的值基本上是完全重合的。
根據此實驗的趨勢就可以看到，當μ（表中顯示為mu）上升，很顯然的，整個系統的等待時間就會下降，相對的在系統中的人數也是下降。
![image]https://github.com/thumbd78492/MMSK_QueueingModel_Analysis/blob/main/pics/mu_Ls.png
![image]https://github.com/thumbd78492/MMSK_QueueingModel_Analysis/blob/main/pics/mu_Lq.png
![image]https://github.com/thumbd78492/MMSK_QueueingModel_Analysis/blob/main/pics/mu_Ws.png
![image]https://github.com/thumbd78492/MMSK_QueueingModel_Analysis/blob/main/pics/mu_Wq.png
  
  
 
接下來是改變平行服務者（server）的數量，因為M/G/1沒辦法進行設置，所以接下來的部分只針對M/M/s/∞及G/M/m/∞進行比較。
環境的設置分別是：λ=4.0,μ=6.0
可以看到，隨著平行服務者的上升，系統平均的等待時間會很顯著的下降。
![image]https://github.com/thumbd78492/MMSK_QueueingModel_Analysis/blob/main/pics/s_Ls.png
![image]https://github.com/thumbd78492/MMSK_QueueingModel_Analysis/blob/main/pics/s_Lq.png
![image]https://github.com/thumbd78492/MMSK_QueueingModel_Analysis/blob/main/pics/s_Ws.png
![image]https://github.com/thumbd78492/MMSK_QueueingModel_Analysis/blob/main/pics/s_Wq.png
  
 
最後是改變queue的長度，同樣的，因為M/G/1沒辦法進行設置，所以接下來的部分是針對M/M/s/k及G/M/m/k進行比較。
環境的設置為：λ=4.0,μ=6.0,平行服務者(s/m)的數量設置為2
相較之前的實驗，在這一項目的模擬是比較有波動的情形，我想這是因為在queue的長度受限的情況下，模擬期間顧客被drop的數量很大程度的影響了模擬的結果，假如做足夠多次的模擬取平均值，應該就能得到一個圓滑的結果。
相對模擬，數學分析計算出來的曲線當然很圓滑，但是它與模擬的曲線還是非常契合的。

可以看到，隨著k的上升，G/M/m/k（其中G是採uniform distribution）模型的等待時間上升是比較平緩的。這說明了顧客抵達採uniform distribution的inter-arrival time相較exponential distribution要來得更鬆散。
![image]https://github.com/thumbd78492/MMSK_QueueingModel_Analysis/blob/main/pics/k_Ls.png
![image]https://github.com/thumbd78492/MMSK_QueueingModel_Analysis/blob/main/pics/k_Lq.png
![image]https://github.com/thumbd78492/MMSK_QueueingModel_Analysis/blob/main/pics/k_Ws.png
![image]https://github.com/thumbd78492/MMSK_QueueingModel_Analysis/blob/main/pics/k_Wq.png
