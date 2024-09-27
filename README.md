# LVGL Manager

## Page

每一个页面都要实现 `lv_mgr_page_interface_t` 内的函数，并用宏 `LV_MGR_PAGE_REG` 注册页面。具体可以看 `src/gui/page` 的页面实现。

值得注意的是，调度器根据 id 寻找页面，切勿出现两个页面 id 相同的情况。

```c
/**
 * @brief 根据 id 跳转页面
 **/
lv_mgr_status lv_mgr_page_push(int32_t page_id, bool anim);

/**
 * @brief 回到上一页面
 **/
lv_mgr_status lv_mgr_page_pop(bool anim);
```

