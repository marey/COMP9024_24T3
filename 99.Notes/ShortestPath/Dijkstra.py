# 设置一个非常大的数字来表示无穷大
INF = 99999999


def find_shortest_dist(vSet, dist):
    # 开始找找最小的
    # 设置一个无穷的数字
    shortest_dist = INF
    # 距离最小的那个顶点
    shortest_dist_v = -1
    # 剩余顶点里面的每个顶点，检查距离最小的那个
    for v in vSet:
        # 判断是否是距离最小的那个
        if dist[v] <= shortest_dist:
            shortest_dist_v = v
            shortest_dist = dist[v]
    # 返回最小的
    return shortest_dist_v


def dijkstra(graph, src, dest):
    # 因为是用矩阵表示的，所以应该是一个V * V的一个矩阵
    number_of_vertices = len(graph)
    # 判断是在范围之内
    if not 0 <= src < number_of_vertices and 0 <= dest < number_of_vertices:
        return

    # 创建dist和pred
    # 起点是0，其他为无穷大
    dist = [0 if src == i else INF for i in range(number_of_vertices)]
    # 全都这是为 -1
    pred = [-1 for i in range(number_of_vertices)]
    # 存放所有的点的vSet
    vSet = set(range(number_of_vertices))
    # 判断vSet不为空
    while vSet:
        # 从dist里面找到最小的点
        s = find_shortest_dist(vSet, dist)
        # 判断是否有一条边
        for t in range(number_of_vertices):
            # 获取权重
            weight = graph[s][t]
            # 判断是否需要relax，权重weight > 0表示存在一条边
            if weight > 0 and dist[s] + weight < dist[t]:
                # relaxation，更新距离
                dist[t] = dist[s] + weight
                # 绑定关系，s 可以到 t
                pred[t] = s
        # vSet \ s, 删除掉 s
        vSet.discard(s)

    # 获取最短的距离
    if dist[dest] < INF:  # 表示可以从src访问到dest,
        print(f"从起点: {src} 到终点: {dest}的最短距离是: {dist[dest]}")
        # 利用stack反向查找路径，正向输出
        stack = []
        pred_v = dest
        # 从终点向起点方向查找
        while pred_v != -1:
            # 添加点
            stack.append(pred_v)
            pred_v = pred[pred_v]
        # 从起点向终点正向输出
        while stack:
            print(f"{stack.pop()}")
    else:
        print(f"起点: {src} 到终点: {dest} 没有最短距离! ")


# 从文件中读取数据
def read_graph_from_file(file_name):
    # 它是一个matrix的二维列表
    graph = []
    # 打卡文件
    with open(file_name) as file:
        # 默认输出都是对的
        for line in file:
            # 如果是空行就跳过
            if line.isspace():
                continue
            # 开始处理每行数据
            rows = [int(x) for x in line.split()]
            # 添加每行数据
            graph.append(rows)

    return graph


if __name__ == "__main__":
    file_name = input("请输入文件名（文件名必须与当前py文件在同一个目录）: ")
    src, dest = input("请输入两个表示起点和终点的数字: ").split()
    # 读取graph
    graph = read_graph_from_file(file_name)
    # 执行算法
    dijkstra(graph, int(src), int(dest))
