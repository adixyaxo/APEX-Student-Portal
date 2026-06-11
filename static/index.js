/* ============================================================
   APEX — Index / Rankings JS
   ============================================================ */

/* ── Live search ── */
const searchInput   = document.getElementById('rankSearch');
const rankingRows   = document.querySelectorAll('.rank-row');

if (searchInput) {
  searchInput.addEventListener('input', () => {
    const q = searchInput.value.toLowerCase().trim();

    rankingRows.forEach(row => {
      const name = row.querySelector('.student-name')?.textContent.toLowerCase() ?? '';
      const id   = row.querySelector('.col-id')?.textContent.toLowerCase() ?? '';
      const match = !q || name.includes(q) || id.includes(q);
      row.style.display = match ? '' : 'none';
    });
  });
}

/* ── Row hover: restore opacity on hover, reset on leave ── */
rankingRows.forEach(row => {
  // Row opacity is handled by CSS :hover override
  // Nothing extra needed, just ensure a11y keyboard focus is visible
  row.setAttribute('tabindex', '0');
});

/* ── Filter button placeholder ── */
const filterBtn = document.getElementById('filterBtn');
if (filterBtn) {
  filterBtn.addEventListener('click', () => {
    // TODO: connect to filter dropdown when backend is ready
    filterBtn.textContent = filterBtn.textContent.includes('✕')
      ? '⊞ Filter'
      : '✕ Clear';
  });
}
