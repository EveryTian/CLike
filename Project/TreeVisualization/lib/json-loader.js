function buildTree(treeData, treeContainerDom) {
    const depthHeight = 80;
    const timeInterval = 800;

    const margin = {top: 40, right: 120, bottom: 20, left: 120};
    // const width = 1366 - margin.right - margin.left;
    // const height = 1366 - margin.top - margin.bottom;
    const [width, height] = [1366, 1366];
    const duration = 750;
    const tree = d3.layout.tree().size([height, width]);
    const diagonal = d3.svg.diagonal().projection(d => [d.x, d.y]);
    const svg = d3.select(treeContainerDom).append("svg")
        .attr("width", width + margin.right + margin.left)
        .attr("height", height + margin.top + margin.bottom)
        .append("g").attr("transform", "translate(" + margin.left + "," + margin.top + ")");
    const root = treeData;
    let i = 0;
    const clickNode = d => {
        if (d.children) {
            d.nodes = d.children;
            d.children = null;
        } else {
            d.children = d.nodes;
            d.nodes = null;
        }
        update(d);
    };
    const update = source => {
        const nodes = tree.nodes(root).reverse();
        const links = tree.links(nodes);
        nodes.forEach(d => {
            d.y = d.depth * depthHeight;
        });
        const node = svg.selectAll("g.node").data(nodes, d => d.id || (d.id = ++i));
        const nodeEnter = node.enter().append("g").attr("class", "node")
            .attr("transform", () => "translate(" + source.x0 + "," + source.y0 + ")")
            .on("click", clickNode);
        nodeEnter.append("circle").attr("r", 10)
            .attr("stroke", d => d.children || d.nodes ? "steelblue" : "#00c13f")
            .style("fill", d => d.children || d.nodes ? "lightsteelblue" : "#fff");
        nodeEnter.append("text").attr("y", d => d.children || d.nodes ? -18 : 18)
            .attr("dy", ".35em").attr("text-anchor", "middle").text(d => d.name)
            .style("fill-opacity", 1e-6);
        const nodeUpdate = node.transition().duration(duration)
            .attr("transform", d => "translate(" + d.x + "," + d.y + ")");
        nodeUpdate.select("circle").attr("r", 10).style("fill", d => d.nodes ? "lightsteelblue" : "#fff");
        nodeUpdate.select("text").style("fill-opacity", 1);
        const nodeExit = node.exit().transition().duration(duration)
            .attr("transform", () => "translate(" + source.x + "," + source.y + ")").remove();
        nodeExit.select("circle").attr("r", 1e-6);
        nodeExit.select("text").style("fill-opacity", 1e-6);
        const link = svg.selectAll("path.link").data(links, d => d.target.id);
        link.enter().insert("path", "g").attr("class", "link")
            .attr("d", () => diagonal({source: {x: source.x0, y: source.y0}, target: {x: source.x0, y: source.y0}}));
        link.transition().duration(duration).attr("d", diagonal);
        link.exit().transition().duration(duration).attr("d", () => {
            const o = {x: source.x, y: source.y};
            return diagonal({source: o, target: o});
        }).remove();
        nodes.forEach(d => {
            d.x0 = d.x;
            d.y0 = d.y;
        });
    };
    update(root);
    const autoOpen = (head, time) => {
        window.setTimeout(() => {
            clickNode(head);
            if (head.children) {
                let timeOut = timeInterval;
                head.children.forEach(child => {
                    autoOpen(child, timeOut);
                    timeOut = timeOut + timeInterval;
                });
            }
        }, time);
    };
    autoOpen(root, timeInterval);
}

function generate(str) {
    const lines = str.split('\n').filter(x => x !== '');
    lines.shift();
    const root = {
        name: '#Program',
        nodes: [],
        nodesNames: ['**glbDecList']
    };
    let curLine = [root];
    for (let line of lines) {
        const nextLine = [];
        let nextLineNodes = line.split('|').filter(x => x !== '');
        let i = 0;
        for (let node of curLine) {
            for (let childNodeIndex = 0; childNodeIndex < node.nodesNames.length; ++childNodeIndex) {
                const childNodeName = node.nodesNames[childNodeIndex];
                if (typeof childNodeName !== 'string') {
                    continue;
                }
                if (childNodeName.startsWith('**')) {
                    let namePrefix = undefined;
                    while (i < nextLineNodes.length) {
                        const [name, ...childrenNodesName] = nextLineNodes[i].split(' ');
                        const newNamePrefix = name.substring(0, 5);
                        if (namePrefix === undefined) {
                            namePrefix = newNamePrefix;
                        } else if (namePrefix !== newNamePrefix) {
                            break;
                        }
                        const newNode = {
                            name: name,
                            nodes: [],
                            nodesNames: childrenNodesName,
                        };
                        node.nodes.push(newNode);
                        nextLine.push(newNode);
                        ++i;
                    }
                } else if (childNodeName.startsWith('*')) {
                    if (!nextLineNodes[i]) {
                        continue;
                    }
                    const [name, ...childrenNodesName] = nextLineNodes[i++].split(' ');
                    const newNode = {
                        name: name,
                        nodes: [],
                        nodesNames: childrenNodesName,
                    };
                    node.nodes.push(newNode);
                    nextLine.push(newNode);
                }

            }
            curLine = nextLine;
        }
    }
    return root;
}
