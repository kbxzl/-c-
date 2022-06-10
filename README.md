题目要求：ratings.csv中的每一行分别保存着userid,moiveid,rating（0-5分，有小数）和timestamp
在movies.csv中的每一行moiveid,title和genres(类别)
你要做的就是对于ratings.csv的每一个用户评分，判断该用户是否喜欢该影片(评分>=3),如果喜欢，则在movies.csv中找到其对应的类型并记录，最后机型汇总，计算每一个用户喜欢的电影类型和数目，保存到result.csv中，例如：

在ratings.csv中：
userId,movieId,rating,timestamp
1,1,4,964982703
1,3,4,964981247
1,6,4,964982224
2,278,3,1445714835
2,292,4,1445715029

在其对应的moives.csv中：
movieId,title,genres
1,Toy Story (1995),Adventure|Animation|Children|Comedy|Fantasy
3,Grumpier Old Men (1995),Comedy|Romance
6,Heat (1995),Action|Crime|Thriller
278,"Shawshank Redemption, The (1994)",Crime|Drama
292,Tommy Boy (1995),Comedy

则result.csv为：
1:Adventure 1 |Animation 1 |Children 1 |Comedy 2 |Fantasy 1 |Romance 1 |Action 1 |Crime 1 |Thriller 1 
2:Crime 1 |Drama 1 |Comedy 1 
#注意输出格式
