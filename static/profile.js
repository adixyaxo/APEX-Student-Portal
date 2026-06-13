
const addBtn   = document.getElementById('addSubjectBtn');
const panel    = document.getElementById('addSubjectPanel');
const closeBtn = document.getElementById('closeAddPanel');
const cancelBtn = document.getElementById('cancelAddSubj');

function openPanel()  { if (panel) panel.style.display = ''; }
function closePanel() { if (panel) panel.style.display = 'none'; }

if (addBtn)   addBtn.addEventListener('click', openPanel);
if (closeBtn) closeBtn.addEventListener('click', closePanel);
if (cancelBtn) cancelBtn.addEventListener('click', closePanel);