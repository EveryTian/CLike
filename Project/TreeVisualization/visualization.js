document.getElementById('load').onclick = () => document.getElementById('file-port').click();
document.getElementById('file-port').onchange = () => {
    const file = document.getElementById('file-port').files[0];
    if (!file) {
        return;
    }
    const reader = new FileReader();
    reader.onload = event => {
        try {
            buildTree(generate(event.target.result), "#tree");
        } catch (e) {
            alert('Loading failed...');
        }
    };
    reader.readAsText(file);
};
